#include<bits/stdc++.h>
#include<jsoncpp/json/json.h>
#include<mysql_connection.h>
#include<cppconn/driver.h>
#include<cppconn/exception.h>
#include<cppconn/resultset.h>
#include<cppconn/statement.h>
#define infi 1000000000
using namespace std;
using namespace sql;
using namespace Json;
void fun(int a[][8]);
class City{
	public:
	int cityId;
	vector<pair<int, int> > neighbour;
	City(int cityId){
		this->cityId = cityId;
	}
	void add_neighbour(int cityId, int fare){
		pair<int, int> p;
		p.first = cityId;
		p.second = fare;
		neighbour.push_back(p);
	}
};
int minFare(vector<City*> g,int s,int d, vector<int>& path){
	vector<int> dist(g.size());
	bool visited[g.size()];
	for (int i = 0; i < g.size(); i++) {
		visited[i] = false;
		path[i] = -1;
		dist[i] = infi;
	}
	dist[s] = 0;
	path[s] = -1;
	int current = s;
	unordered_set<int> sett;
	while (true) {
		visited[current] = true;
		for (int i = 0; i< g[current]->neighbour.size();i++) {
			int v = g[current]->neighbour[i].first;
			if (visited[v])continue;
			sett.insert(v);
			int alt= dist[current]+ g[current]->neighbour[i].second;
			if (alt < dist[v]) {
				dist[v] = alt;
				path[v] = current;
			}
		}
		sett.erase(current);
		if (sett.empty())
			break;
		int minDist = infi;
		int index = 0;
		for (int a: sett) {
			if (dist[a] < minDist) {
				minDist = dist[a];
				index = a;
			}
		}
		current = index;
	}
	return dist[d];
}
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
                int a[8][8];
                fun(a);
                ResultSet& rs=*stmt.executeQuery("select * from farelist");
                        while(rs.next()){
                                stringstream g(rs.getString(3));
                                int r;
                                g>>r;
                                a[rs.getInt(1)][rs.getInt(2)]=r;
                                a[rs.getInt(2)][rs.getInt(1)]=r;
                        }
                cout<<"Insert source and destination city name "<<endl;
                string s1,s2;
		cout<<"Source city name"<<endl;
                cin>>s1;
		cout<<"Destination city name"<<endl;
		cin>>s2;
		g:
                ResultSet& rs1=*stmt.executeQuery("select * from city_master where city_name='"+s1+"'");
                ResultSet& rs2=*stmt.executeQuery("select * from city_master where city_name='"+s2+"'");
                int sor=0,des=0;
                while(rs1.next()){
                        sor=rs1.getInt(1);
                }
		while(rs2.next()){
                        des=rs2.getInt(1);
                }
		if(sor==0){
			cout<<s1<<" doesn't exist"<<endl;
			cout<<"Source city name again insert"<<endl;
			cin>>s1;
			goto g;
		}else if(des==0){
			cout<<s2<<" doesn't exist"<<endl;
			cout<<"Destination city name again insert"<<endl;
			cin>>s2;
			goto g;
		}
		vector<City*> v;
	        int n = 8;
        	for (int i = 0; i < n; i++) {
                	City* a = new City(i);
                	v.push_back(a);
        	}
		for(int i=0;i<8;i++){
                	for(int j=0;j<8;j++){
                        	if(a[i][j]==0||a[i][j]==-1){
                        	        continue;
                        	}else{
                        	        v[i]->add_neighbour(j,a[i][j]);
                        	}
        	        }
	        }
        vector<int> path(v.size());
        int minimumfare= minFare(v, sor, des, path);
        cout<<"minimum fare between "<<s1<<"("<<sor<<")"<< " and "<<s2<<"("<<des<<")"<<" is: "<<minimumfare<<endl;
        }catch(SQLException &e){
                cout<<"Error"<<e.what()<<endl;
        }
return 0;
}
void fun(int a[8][8]){
        for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                        if(i==j &&i>=1&&j>=1){
                                a[i][j]=0;
                        }else{
                                a[i][j]=-1;
                        }
                }
        }
}
