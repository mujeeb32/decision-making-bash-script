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
int main(){
	Reader creader;
        Value cobj;
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
                ResultSet& rs1=*stmt.executeQuery("select * from city_master");
                while(rs1.next()){
                        cout<<"id="<<rs1.getInt(1)<<" "<<"city name="<<rs1.getString(2)<<endl;
                }
        }catch(SQLException &e){
                cout<<"Error"<<e.what()<<endl;
        }
return 0;
}
