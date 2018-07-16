using namespace std;

#include <fstream>
#include <sstream>
#include <math.h>
#include <vector>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_cdf.h>


vector<double> pi1_vec;
vector<double> epip_vec;
vector<string> snp_vec;
vector<double> bf_vec;

void init();
void process_data(char *infile);
void compute_pip();
double compute_log10_BF(double z_score);
double log10_weighted_sum(vector<double> &vec, vector<double> &wts);



string curr_gene = string("");

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
        double zval;
        double epip;
        double cpip = 0;
        if(ins>>snp>>gene>>zval>>epip){

                  
            if(curr_gene != gene){
                if(snp_vec.size()>0){
                    compute_pip();
                }
                curr_gene = gene;
                pi1_vec.clear();
                bf_vec.clear();
                epip_vec.clear();
                snp_vec.clear();
            }

            double pi1 = epip*pi1_eqtl + (1-epip)*pi1_null;
            double log10_BF = compute_log10_BF(zval);
            pi1_vec.push_back(pi1);
            bf_vec.push_back(log10_BF);
            epip_vec.push_back(epip);
            snp_vec.push_back(snp);
        }

    }
    compute_pip();
    return; 
}










void compute_pip(){


    vector<double> pip_vec;

    int p = snp_vec.size();
    vector<double> wts(p+1,1.0);
    vector<double> postv;
    for(int i=0;i<p;i++){
        double val = log10(pi1_vec[i])-log10(1.0 - pi1_vec[i])+ bf_vec[i];
        postv.push_back(val);
    }

    postv.push_back(0.0);
    double log10NC = log10_weighted_sum(postv,wts);

    for(int i=0;i<p;i++){
        double pip = pow(10.0,postv[i]-log10NC);
        printf("%15s  %15s  %7.3e  %7.3e\n", snp_vec[i].c_str(), curr_gene.c_str(), pi1_vec[i], pip);
    }
}





double compute_log10_BF(double z_score){
    double kv[4] = {1,4,16,25};
    int size = 4;
    double z2 = pow(z_score, 2.0);
    vector<double> rstv;
    vector<double> wtv(size,1.0/double(size));
    for(int i=0;i<size;i++){

        double val = 0.5*log(1/(1+kv[i])) + 0.5*z2*(kv[i]/(1+kv[i]));
        rstv.push_back(val/log(10));
    }

    return log10_weighted_sum(rstv,wtv);
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

