#!/usr/bin/env python
# -*- coding:utf-8 -*-

import string
import re
import urllib2

class Movie(object) :
    
    def __init__(self) :
        self.m_id = 0
        self.m_source_id = 0
        self.m_name = ""
        self.m_score = 0.0
        self.m_year = 0
        self.m_region = []
        self.m_type = []
        self.m_introduction = ""
        

class DouBanSpider(object) :

    def __init__(self) :
        self.page = 1
        self.cur_url = "http://movie.douban.com/top250?start={page}&filter=&type="
        self.datas = []
        self.m_index = 1
        
        print "start crawling ..."
        
        
    def get_movie_type(types) :
        movie_type = []
        for item in enumerate(types) :
            movie_type.append(string_to_movie_type(item))
        return movie_type

    def get_page(self, cur_page) :

        url = self.cur_url
        try :
            #fin = file('data.in', 'r')
            #my_page = fin.read()
            #fin.close()
            my_page = urllib2.urlopen(url.format(page = (cur_page - 1) * 25)).read().decode("utf-8")
        except urllib2.URLError, e :
            if hasattr(e, "code"):
                print "The server couldn't fulfill the request."
                print "Error code: %s" % e.code
            elif hasattr(e, "reason"):
                print "We failed to reach a server. Please check your url and read the Reason"
                print "Reason: %s" % e.reason
        return my_page


    def find_title(self, my_page) :
        
        #movie_id = re.findall(r'<em class="">(+)</em>', my_page, re.S)
        movie_name = re.findall(r'<img alt="(.*?)" src=', my_page, re.S)
        movie_source_id = re.findall(r'<a href="http://movie.douban.com/subject/(\d+)/" class=""', my_page, re.S)
        movie_score = re.findall(r' <span class="rating\d+-t"><em>(.*?)</em></span>', my_page, re.S)
        movie_year = re.findall(r'<br>\n +(\d+).*?&nbsp;/&nbsp.*?&nbsp;/&nbsp;', my_page, re.S)
        
        l_region = re.findall(r'<br>\n +\d+.*?&nbsp;/&nbsp;(.*?)&nbsp;/&nbsp;', my_page, re.S);
        movie_region = []
        for item in enumerate(l_region) :
            l_r = re.split(r'[ \t]+', item[1])
            movie_region.append(l_r)
            
        l_type = re.findall(r'<br>\n +\d+.*?&nbsp;/&nbsp;.*?&nbsp;/&nbsp;(.*?)[ \t]*\n', my_page, re.S);
        movie_type = [];
        for item in enumerate(l_type) :
            l_t = re.split(r'[ \t]+', item[1])
            movie_type.append(l_t)
            
        print 'len : ', len(movie_name), len(movie_source_id), len(movie_score), len(movie_year), len(movie_region), len(movie_type)
        
        #print movie_year
        #print movie_region
        #print movie_type
        
        for k in range(len(movie_name)) :
            m = Movie()
            m.m_id = self.m_index
            self.m_index = self.m_index + 1
            m.m_name = movie_name[k]
            m.m_source_id = movie_source_id[k]
            m.m_score = movie_score[k]
            m.m_year = movie_year[k]
            m.m_region = movie_region[k]
            m.m_type = movie_type[k]
            self.datas.append(m)
        
    
    def start_spider(self) :

        while self.page <= 10 :
            print 'crawling page ' + str(self.page) + ' ... ...'
            my_page = self.get_page(self.page)
            self.find_title(my_page)
            self.page += 1
            
        print 'end crawling ...'
        
        fout = file('movie.dat', 'w')
        for index, item in enumerate(self.datas) :
            fout.write(str(item.m_id))
            fout.write('|')
            fout.write(item.m_name.encode('gbk'))
            fout.write('|')
            fout.write(item.m_source_id)
            fout.write('|')
            fout.write(item.m_score)
            fout.write('|')
            fout.write(item.m_year)
            fout.write('|')
            fout.write(' '.join(item.m_region).encode('gbk'))
            fout.write('|')
            fout.write(' '.join(item.m_type).encode('gbk'))
            fout.write('\n')
        fout.close()
        print 'write to movie.dat ...'

def main() :
    
    my_spider = DouBanSpider()
    my_spider.start_spider()

if __name__ == '__main__':
    main()
