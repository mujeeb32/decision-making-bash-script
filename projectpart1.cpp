#include<bits/stdc++.h>
#include<jsoncpp/json/json.h>
#include<mysql_connection.h>
#include<cppconn/driver.h>
#include<cppconn/exception.h>
#include<cppconn/resultset.h>
#include<cppconn/statement.h>
using namespace std;
using namespace sql;
using namespace Json;
int main(int argc,char* argv[]){
	if(argc!=2){
		cout<<"Json file missing"<<endl;
		return 0;
	}
	ifstream ifs(argv[1]);
        Reader reader;
        Value obj;
	Reader creader;
	Value cobj;
        reader.parse(ifs,obj);
	ifstream cifs("link.json");
	creader.parse(cifs,cobj);
	const string url=cobj["url"].asString();
        const string user=cobj["username"].asString();
        const string pass=cobj["password"].asString();
        const string database=cobj["database"].asString();
	try{
        Driver& driver=*get_driver_instance();
        Connection& con=*driver.connect(url,user,pass);
        con.setSchema(database);
        Statement& stmt=*con.createStatement();
	Value::Members v=obj.getMemberNames();
	stmt.execute("delete from farelist");
	for(Value::Members::iterator it1=v.begin();it1!=v.end();it1++){
		string s1=*it1;
		Value::Members v1=obj[s1].getMemberNames();
		for(Value::Members::iterator it2=v1.begin();it2!=v1.end();it2++){
			string s2=*it2;
			string s3=obj[s1][s2].asString();
	stmt.execute("insert into farelist values((select city_id from city_master where(city_name='"+s1+"')),(select city_id from city_master where(city_name='"+s2+"')),'"+s3+"')");
		}
	}
	cout<<"run success fully!!"<<endl;
	}catch(SQLException &e){
		cout<<"Error"<<e.what()<<endl;
	}
return 0;
}

