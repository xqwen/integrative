using namespace std;

#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


vector<double> pi1_vec;
vector<double> epip_vec;
vector<string> snp_vec;
vector<double> gpip_vec;

void init();
void process_data(char *infile);
void compute_rcp();



string sig_id = string("");

double pi1_eqtl;
double pi1_null;

double a0 = -99999;
double a1 = -99999;

int main(int argc, char **argv){

    char data_file[128];
    for(int i=1;i<argc;i++){   

        if(strcmp(argv[i], "-d")==0 || strcmp(argv[i], "-data")==0){
            strcpy(data_file,argv[++i]);
            continue;
        }

        if(strcmp(argv[i], "-a1")==0 ){
            a1 = atof(argv[++i]);
            continue;
        }


        if(strcmp(argv[i], "-a0")==0 ){
            a0 = atof(argv[++i]);
            continue;
        }



    }
    init();
    process_data(data_file);


}

void init(){
    if(a0 == -99999){
        fprintf(stderr, "Error: a0 is not specified\n");
        exit(1);
    }
    if(a1  == -99999){
        fprintf(stderr, "Error: a1 is not specified\n");
        exit(1);
    }
    pi1_null = exp(a0)/(1+exp(a0));
    pi1_eqtl =  exp(a0+a1)/(1+exp(a0+a1));
}

void process_data(char *in_file){

    ifstream gfile(in_file);
    string line;
    istringstream ins;
    int count = 0;
    while(getline(gfile,line)){

        ins.clear();
        ins.str(line);

        string snp;
        string gene;
        string sig;
        double gpip;
        double epip;
        double cpip = 0;
        if(ins>>gene>>sig>>snp>>epip>>gpip){
            string sid = gene+":"+sig;      
            if(sid != sig_id){
                if(snp_vec.size()>0){
                    compute_rcp();
                }
                sig_id = sid;
                pi1_vec.clear();
                epip_vec.clear();
                snp_vec.clear();
                gpip_vec.clear();
            }

            double pi1 = epip*pi1_eqtl + (1-epip)*pi1_null;
            pi1_vec.push_back(pi1);
            epip_vec.push_back(epip);
            snp_vec.push_back(snp);
            gpip_vec.push_back(gpip);
        }

    }
    compute_rcp();
    return; 
}




void compute_rcp(){

    int p = snp_vec.size();
    double max_ccp = -1;
    string max_snp;
    double cum_epip = 0;
    double cum_gpip = 0;
    double cum_colocp = 0;
    double max_z_abs = 0;
    string max_z_snp;
    for(int i=0;i<p;i++){
        double gpip = gpip_vec[i];
        cum_gpip += gpip;
        double epip = epip_vec[i];
        cum_epip += epip;

        double colocp = gpip/(1+((1-epip)/epip)*( (1+exp(a0+a1))/(exp(a1)+exp(a0+a1)) ));
        if(colocp> max_ccp){
            max_ccp = colocp;
            max_snp = snp_vec[i];
        }
        cum_colocp += colocp;
    }

    double hyp_colocp = cum_gpip/(1+((1-cum_epip)/cum_epip)*( (1+exp(a0+a1))/(exp(a1)+exp(a0+a1)) ));

    printf("%20s  %7.3f %7.3f  %4d   %7.3e   %15s %7.3e\n", sig_id.c_str(), cum_epip, cum_gpip, p, cum_colocp,   max_snp.c_str(), max_ccp);
}






double log10_weighted_sum(vector<double> &vec, vector<double> &wts){


    double max = vec[0];
    for(size_t i=0;i<vec.size();i++){
        if(vec[i]>max)
            max = vec[i];
    }
    double sum = 0;
    for(size_t i=0;i<vec.size();i++){
        sum += wts[i]*pow(10, (vec[i]-max));
    }

    return (max+log10(sum));
}

