#include <vector>
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <iostream>
#include <zcm/zcm-cpp.hpp>
#include "common_utils.h"
#include "CleanMachine.h"
#include "Point_5D.h"
#include "common.h"
#include "msg_header_z.hpp"
#include "navigation_msg_z.hpp"
#include "localmap_dense_msg_z.hpp"
#include "control_msg_z.hpp"
#include "vehicle_misc_msg_z.hpp"
#include "object_msg_z.hpp"
#include "canmsg_msg_z.hpp"
#include "lidar_curb_msg_z.hpp"
#include "line_msg_z.hpp"

using namespace std;
using namespace cma::commonutils;

class Handler {
    public:
    ~Handler() {}

std::mutex NAVmtx;
std::mutex MAPmtx;
std::mutex OBJmtx;
std::mutex CURBmtx;
std::mutex CANmtx;
std::mutex TRAJmtx;
std::mutex EVENTmtx;
std::mutex LINEmtx;
    
navigation_msg_z buffer_navinfo;
localmap_dense_msg_z buffer_map;
vehicle_misc_msg_z buffer_event;
canmsg_msg_z buffer_can;
control_msg_z buffer_traj;
object_msg_z buffer_obj;
lidar_curb_msg_z buffer_curb;
line_msg_z buffer_line;

bool is_navinfo_received;
bool is_map_received;
bool is_canmsg_received;
bool is_curbinfo_received;
bool is_object_received;
bool is_laneline_received;

int Curbnum[2] = {0, 0};

    void handleMessage_navinfo(const zcm::ReceiveBuffer* rbuf,
	const string& chan,
	const navigation_msg_z *msg)
    {
        NAVmtx.lock();
        buffer_navinfo = *msg;
        NAVmtx.unlock();
    	is_navinfo_received = true;
        return ;
	}
    void handleMessage_map(const zcm::ReceiveBuffer* rbuf,
	const string& chan,
	const localmap_dense_msg_z *msg)
    {
        MAPmtx.lock();
        buffer_map = *msg;
        MAPmtx.unlock();
		is_map_received = true;
        return ;
    }
    void handleMessage_object(const zcm::ReceiveBuffer* rbuf,
	const string& chan,
	const object_msg_z *msg)
    {
	cout << "111111111111111111111111111111111111111111" << endl;
        //OBJmtx.lock();
	std::unique_lock<std::mutex> lck(OBJmtx);
        buffer_obj = *msg;
        //OBJmtx.unlock();
		is_object_received = true;
	cout << "22222222222222222222222222222222222222222222222222222222222222222" << endl;
        return ;
    }
    void handleMessage_canmsg(const zcm::ReceiveBuffer* rbuf,
	const string& chan,
	const canmsg_msg_z *msg)
    {
        CANmtx.lock();
        buffer_can = *msg;
        CANmtx.unlock();
		is_canmsg_received = true;
        return ;
    }
    void handleMessage_curb(const zcm::ReceiveBuffer* rbuf,
	const string& chan,
	const lidar_curb_msg_z *msg)
    {
	CURBmtx.lock();
        buffer_curb = *msg;
	Curbnum[1]++;
        CURBmtx.unlock();
		is_curbinfo_received = true;
        return ;
    }
    void handleMessage_line(const zcm::ReceiveBuffer* rbuf,
	const string& chan,
	const line_msg_z *msg)
    {
        LINEmtx.lock();
        buffer_line = *msg;
        LINEmtx.unlock();
		is_laneline_received = true;
        return ;
    }
};

class MsgManager
{
    public:
    MsgManager();
    void getGridMap(unsigned char _radarData[MAXN][MAXM]);
    void getNavinfo(double &_lat, double &_lon, double &_heading);
    bool getPedestrain(int &_num);
    void getCurbinfo(bool &_iscurb, double &_curbdis);
	bool getLaneline(vector<line_z> &_line);
    void sendTraj(vector<Point_5D> &_traj, double _lateral_Dev, double _heading_Dev, double _speed, bool &_curbflag);
    void sendEvent(CleanMachine &_cleanmachine);
    bool getAuto();
    void zcm_rec();
    
    private:
    zcm::ZCM zcm_sender{"ipc"}; 
    Handler handlerObject;

    int64_t CurbTime[2] = {0, 0};

};
