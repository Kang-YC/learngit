#include <msg_manager.h>
#include <math.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "angle.h"
#include "basic_coordinate_converter.h"
#include <iomanip>

MsgManager :: MsgManager()
{
	handlerObject.is_navinfo_received = false;
	handlerObject.is_map_received = false;
	handlerObject.is_canmsg_received = false;
	handlerObject.is_curbinfo_received = false;
	handlerObject.is_object_received = false;
	handlerObject.is_laneline_received = false;
        CurbTime[0] = GetTimeStamp();
        CurbTime[1] = GetTimeStamp();

    std :: thread zcm_receiver(&MsgManager :: zcm_rec, this);
    zcm_receiver.detach(); 
}

void MsgManager :: getGridMap(unsigned char _radarData[][MAXM])
{
    if(1)
    {
	handlerObject.is_map_received = false;
        handlerObject.MAPmtx.lock();
        //MapTime[1] = handlerObject.buffer_map.header.timestamp;
        //if(MapTime[1] - MapTime[0] != 0)
        //{
            memset(_radarData, 0, sizeof(_radarData));
            for(int i=0; i<MAXN; i++)
            {   
                for(int j=0; j<MAXM; j++)
                {
                    if(i >= handlerObject.buffer_map.data.rows || j >= handlerObject.buffer_map.data.cols) continue;
                    _radarData[i][j] = handlerObject.buffer_map.data.grid[0][i][j];
                }
            }
        //    Mapnum = 0;
        //}
        //else
        //{
        //    Mapnum++;
        //}
        //MapTime[0] = MapTime[1];
        handlerObject.MAPmtx.unlock();
        //if(Mapnum >= 500)
        //{
        //    cout << "The radarMap zcm does not update!" << endl;
        //    return false;
        //}
    }

    return ;
}

void MsgManager :: getNavinfo(double &_lat, double &_lon, double &_heading)
{
    if(1)
    {
		handlerObject.is_navinfo_received = false;
        handlerObject.NAVmtx.lock();
        //NavTime[1] = handlerObject.buffer_navinfo.header.timestamp;
        //if(NavTime[1] - NavTime[0] != 0)
        //{
            _lat = handlerObject.buffer_navinfo.data.latitude;
            _lon = handlerObject.buffer_navinfo.data.longitude;
            _heading = handlerObject.buffer_navinfo.header.pose.heading;
        //    Navnum = 0;
        //}
        //else
        //{
         //   Navnum++;
        //}
        //if(Navnum >=1000)
        //{
        //    _lat = 90.0;
        //    _lon = 180.0;
        //    _heading = 0;
        //    cout << "There is no location zcm!" << endl;
        //}
        //NavTime[0] = NavTime[1];
        handlerObject.NAVmtx.unlock();
    }

    return ;
}

bool MsgManager :: getPedestrain(int &_num)
{
    //cout << "is_object_received = " << handlerObject.is_object_received << endl;
	//if(handlerObject.is_object_received == true)
	if(1)
    {
		handlerObject.is_object_received = false;
        handlerObject.OBJmtx.lock();
        //ObjTime[1] = handlerObject.buffer_obj.header.timestamp;
        _num = 0;
        for(int i = 0; i < handlerObject.buffer_obj.num_obj; i++)
        {
            if(handlerObject.buffer_obj.objects[i].type == 0)
            {
                 if(fabs(handlerObject.buffer_obj.objects[i].vef_vel.x) > 1.0)
                    continue;
                    
                if(handlerObject.buffer_obj.objects[i].vef_vel.y < 8.0)
                    _num++;
            }
        }
        handlerObject.OBJmtx.unlock();
        if(_num == 0) return false;
        return true;
    }
	else
	{
		_num = 0;
		return false;
	}
}

void MsgManager :: getCurbinfo(bool &_iscurb, double &_curbdis)
{
    if(1)
    {
	handlerObject.is_curbinfo_received = false;
        handlerObject.CURBmtx.lock();
        CurbTime[1] = GetTimeStamp();
        _iscurb = handlerObject.buffer_curb.data.isdetected;
        _curbdis = handlerObject.buffer_curb.data.curbdis;
	if(CurbTime[1] - CurbTime[0] >= 1000)
	{
		if(handlerObject.Curbnum[1] <= handlerObject.Curbnum[0])
		{
			_iscurb = false;
			_curbdis = 0;
		}
		else
		{
			CurbTime[0] = CurbTime[1];
			handlerObject.Curbnum[0] = 0;
			handlerObject.Curbnum[1] = 0;
		}
	}
	cout << "CurbTime[0] = " << CurbTime[0] << endl;
	cout << "CurbTime[1] = " << CurbTime[1] << endl;
        handlerObject.CURBmtx.unlock();
    }

    return ;
}

bool MsgManager :: getLaneline(vector<line_z> &_line)
{
	_line.clear();
    if(handlerObject.is_laneline_received == true)
    {
		handlerObject.is_laneline_received = false;
        handlerObject.LINEmtx.lock();
		int length = handlerObject.buffer_line.length;
		if(length < 1) return false;
		else
		{
			for(int i = 0; i < length; i++)
			{
        		line_z tmp = handlerObject.buffer_line.lines[i];
        		_line.push_back(tmp);
			}
		}
		handlerObject.LINEmtx.unlock();
    return true;
	}
	else return false;
}

void MsgManager :: sendTraj(vector<Point_5D> &_traj, double _lateral_Dev, double _heading_Dev, double _speed, bool &_curbflag)
{
    handlerObject.TRAJmtx.lock();
	trajectory_z tmp;
	tmp.traj_point.clear();
    if(!_curbflag) {
        handlerObject.buffer_traj.type = 0;
    } else {
        handlerObject.buffer_traj.type = 1;
    }
        tmp.num_point = _traj.size(); 
        for(int i = 0; i < _traj.size(); i++) {
		traj_point_z tmp_p;
		tmp_p.pose.utm.x = _traj[i].x;
		tmp_p.pose.utm.y = _traj[i].y;
		tmp.traj_point.push_back(tmp_p);
        }

	handlerObject.buffer_traj.traj = tmp;	
    handlerObject.buffer_traj.dev.speed = _speed;
    handlerObject.buffer_traj.dev.delta_y = _lateral_Dev;
    handlerObject.buffer_traj.dev.delta_angle = _heading_Dev;
    handlerObject.TRAJmtx.unlock();
    zcm_sender.publish("TRAJ_SEND",&handlerObject.buffer_traj);
    return;
}

void MsgManager :: sendEvent(CleanMachine &_cleanmachine)
{
    handlerObject.EVENTmtx.lock();
    handlerObject.buffer_event.status.gear = _cleanmachine.gear;
    handlerObject.buffer_event.status.sweeping = _cleanmachine.sweeping;
    handlerObject.buffer_event.status.water_pump = _cleanmachine.water_pump;
    handlerObject.buffer_event.status.lifting_motor = _cleanmachine.lifting_motor;
    handlerObject.buffer_event.status.lighting = _cleanmachine.lighting;
    handlerObject.buffer_event.status.warning = _cleanmachine.warning;
    handlerObject.buffer_event.status.power = _cleanmachine.power;
    handlerObject.buffer_event.status.trumpet = _cleanmachine.trumpet;
    handlerObject.buffer_event.status.left_steer_light = _cleanmachine.left_steer_light;
    handlerObject.buffer_event.status.right_steer_light = _cleanmachine.right_steer_light;
    handlerObject.buffer_event.header.timestamp = cma::commonutils::GetTimeStamp();
    handlerObject.EVENTmtx.unlock();

    zcm_sender.publish("EVENT_SEND",&handlerObject.buffer_event);

    return;
}

bool MsgManager :: getAuto()
{
    if(1)
    {
		handlerObject.is_canmsg_received = false;
        handlerObject.CANmtx.lock();
        unsigned char automode = 0x00;
        if(handlerObject.buffer_can.canmsg.can_id == 0x211)
            automode = handlerObject.buffer_can.canmsg.data[4] & 0x04;
        handlerObject.CANmtx.unlock();
        
        if(automode == 0x00) return false;
        return true;
    }
}

void MsgManager :: zcm_rec() 
{
    zcm::ZCM zcm{"ipc"};

    if(!zcm.good()) 
    {
        std :: cout << "zcm receiver is not available!" << std :: endl;
        return;
    }
    zcm.subscribe("object",&Handler::handleMessage_object, &handlerObject);
    zcm.subscribe("LOCALMAP_DENSE_MSG", &Handler::handleMessage_map, &handlerObject);
    zcm.subscribe("navigation", &Handler::handleMessage_navinfo, &handlerObject);
   // zcm.subscribe("object", &Handler::handleMessage_object, &handlerObject);
    zcm.subscribe("CAN0_READ", &Handler::handleMessage_canmsg, &handlerObject);
    zcm.subscribe("LIDAR_CURB_MSG",&Handler::handleMessage_curb,&handlerObject);
    zcm.subscribe("LINEVEC_MSG",&Handler::handleMessage_line,&handlerObject);

    while(0 == zcm.handle());
}


