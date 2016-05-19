-------------------- movie_list.dat --------------------
说明:与电影相关数据(豆瓣电影top250资料)
数据格式:
rank|name|id|score|year|region|type
rank:电影在top250中的名次(1-250共250个数字)
name:电影名称
id:豆瓣网中电影ID
score:电影的豆瓣评分
year:电影年份
region:电影地区(可能有不止一个)，详见数据格式
type:电影类型(可能不止一个)，详见数据格式

例子:
1|肖申克的救赎|1292052|9.6|1994|0|0 3
2|这个杀手不太冷|1295644|9.4|1994|5|0 3 6

-------------------- user_info.dat --------------------
说明:与豆瓣用户相关数据
数据格式:
id|name|watched|wanted|review
id:用户id，可能是数字或英文混合
name:用户名字
watched:观看过的电影个数
wanted:想看的电影个数
review:影评个数

例子:
ThinkingCat|思考的猫|412|240|37
jennychang|孤柏岩上的树|147|148|25

-------------------- review_list.dat --------------------
说明:用户对电影的影评数据
数据格式:
user_id|movie_rank|review_id
user_id:用户id，所有用户id均出现在user_inf.dat中
movie_rank:电影排名(1-250)
review_id:影评的id

例子:
ThinkingCat|1|1002421
In-the-cut|1|1023998

-------------------- user_list.dat --------------------
说明:对top250电影影评最多的100个用户，也就是user_info.dat中的用户
数据格式:
id|count
id:用户id
count:在top250个电影中评论的个数

-------------------- review_info文件夹 --------------------
说明:包含了所有的影评数据
数据格式:
每个影评对应一个文件，命名为id.out，其中id为影评id
每个文件中格式(分为三行):
score
title
content
分别表示该影评中用户对电影的评分，影评标题和影评正文
