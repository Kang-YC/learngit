# import pandas as pd
 
# dict=[[1,2,3,4,5,6],[0,0,0,0,0,0]]
# data=pd.DataFrame(dict)
# print(data)
# for indexs in data.index:
#     data.iloc[indexs,0] = 100
#     print(data.loc[indexs].values[0:-1])
# # for indexs in data.index:
# #     print(data.iloc[indexs,0])

# # for indexs in data.columns:
# #     print(data[indexs])

import pandas as pd

inp = [{'c1':10, 'c2':100}, {'c1':11, 'c2':110}, {'c1':12, 'c2':123}]
df = pd.DataFrame(inp)

print(df)

# for row in df.iterrows():
#     row[0] = 5