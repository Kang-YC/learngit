import numpy as np
import pandas as pd
dates = pd.date_range('20130101', periods=6)
df = pd.DataFrame(np.arange(24).reshape((6,4)),index=dates, columns=['A','B','C','D'])
df['E'] = 0
print(df)
df.iloc[5,0] = 19
# df.ix[1,'A']=2
df.iloc[1].A=2
print(df)
print(len(df))
df.rename(columns={'A':'time'}, inplace = True)
print(df)

# count = 0
# for i in range(1, len(df)):
# 	if df.ix[i,'time']- df.ix[i-1,'time'] > 4:
# 		count=count +1
# 		df.ix[i,'E'] = count
		
# 		print('changed')
# 		continue
# 	else:
# 		df.ix[i,'E'] = count
# 		print('no')
# for index, row in df.iterrows():
# 	# print(index) # 输出每行的索引值
# 	print(row)

# for row in df.iterrows():
# 	print(row[0], row[1]) # 输出每一行