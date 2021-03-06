#include <iostream> 
#include <iterator>
#include <algorithm>
//file name: TB_ADC3
void Noise_level(){
	string path;
	int line_size=0;
	int ps=0;
	int alt=0;
	int ch=0;
	int Strip=0;
	int STRIP=0;
	int ALTRO=0;
	int CH=0;
	int Event=0;
	int MaxADC=0;
	int MaxADC_index=0;
	int world=0;
	int TB=0;
	int ADC=0;
	int strip_num=0;
	int adc_num=0;
	int x_strip[470]={0};
	int y_adc[470]={0};
	int x_tb[470]={0};
	int j=0;
	int h=0;
	int EVENT=0;
	int strip_max=0;
	int real_strip[30]={0};
	int real_adc[30]={0};
	vector<int>adc;
	vector<int>tb;
	vector<int>strip;

	int n=0;
	string a;
	string b;
	string c;
	string stor;
	string stor_map;
	string event[11];
	string altro[12];
	TCanvas *c1 = new TCanvas("c1","ADC_TB",800,500);
	TH1F *h1 = new TH1F("h1","Noise ADC",80,0,80);
	c1->SetGrid();

	//**********************************//
	//========== All the File ==========//
	//*********************************//
	int FileBegin=2415;
	int FileEnd=2416;
	for(int k=FileBegin;k<FileEnd;k++){
		ifstream data;
		path=Form("../test_%d.txt",k);
		data.open(path);
		if(!data){
			continue;}

		//	ifstream data;
		//	data.open("./Signal/4.txt");
		ifstream map;

		while(getline(data,stor,'\n')){
			line_size=stor.size();

			ps=stor.find("Event",0);
			if(ps>0){
				if(adc.size()>0){
					EVENT++;
					// The MaxADC,TB and index of this EVENT.
					MaxADC=*max_element(begin(adc),end(adc));
					MaxADC_index=std::distance(begin(adc),std::max_element(begin(adc),end(adc)));
					TB=tb[MaxADC_index];
					strip_max=strip[MaxADC_index];

					//cout <<strip_max<<endl;
					//cout<<"TB: "<<TB<<" MaxADC: "<<MaxADC<<" Index: "<<MaxADC_index<<endl;

					for(int j=0;j<strip.size();j++){
						if(strip[j]==strip_max){
							x_tb[h]=tb[j]-TB;
							y_adc[h]=adc[j];
							h++;
							cout <<"MaxADC StripNum:  "<<strip_max<<" TB: "<<x_tb[h] << " ADC: "<< y_adc[h]<<" "<< h<<endl;
						}
					}


					for(int i=0;i<h;i++){
						if(x_tb[i]<-3){
							h1->Fill(y_adc[i]);}
					}
					h=0;
					n++;

					memset(x_tb,0,sizeof x_strip);
					memset(y_adc,0,sizeof y_adc);
					tb.clear();
					adc.clear();
					strip.clear();
				}
				cout << "The Evnet is : " << EVENT <<endl;
				cout << endl;
				cout << endl;

				istringstream is(stor);
				while(is>>event[world]){world++;}
				event[2].pop_back();
				Event=atoi(event[2].c_str());
				world=0;
			}
			if(Event==30){
			
			break;}
			if(line_size==54){
				istringstream is(stor);
				while(is>>altro[world]){world++;}
				world=0;
				altro[7].pop_back();//ALTRO
				ALTRO=atoi(altro[7].c_str());
				altro[9].pop_back();//CH
				CH=atoi(altro[9].c_str());

				//cout <<ALTRO<<"  "<<CH<<endl;
				map.open("./decode/strip_map_2.txt");
				while(getline(map,stor_map,'\n')){
					istringstream is(stor_map);
					is>>alt>>ch>>Strip;

					if(ALTRO==alt&&CH==ch){
						STRIP=Strip;
					}
				}
				map.close();
				//cout<<"ALTRO:  " <<ALTRO<<" CH: "<<CH<<" Strip:  "<<STRIP<<endl;
			}
			if(ALTRO==50||ALTRO==51||ALTRO==34||ALTRO==35||ALTRO==40||ALTRO==41){
			if(line_size==18){
				istringstream is(stor);
				while(is>>a>>TB>>b>>ADC>>c){
					tb.push_back(TB);
					adc.push_back(ADC);
					strip.push_back(STRIP);		
				}
			}
			}
		}

	}


	cout << "All the Evnet: " << EVENT <<endl;
         h1->GetXaxis()->SetTitle("ADC");
        h1->GetYaxis()->SetTitle("Event");
	h1->Draw();
}
