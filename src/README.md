l# Instructions for enloc

```enloc``` implements the analysis pipeline for enrichment estimation aided colocalization analysis.

## Prerequisite and installation

The single execution point to carry out the full integrative analysis is the perl script ```enloc```, which assumes a few scripts and binary executables pre-installed in the running machine.

* ```torus```: binary executable to carry out the EM algorithm for enrichment estimation. ([repo](https://github.com/xqwen/dap/tree/master/torus_src))
*  ```openmp_wrapper```: binary executable to carry out multi-thread batch processing ([repo](https://github.com/xqwen/openmp_wrapper))
* ```mi_eqtl```: perl script to sample multiple imputation QTL data sets (available in this directory)
* ```get_pip```: perl script to collect QTL posterior inclusion probabilities (PIPs) from QTL analysis results
* ```compute_rcp```: perl script to compute regional colocalization probabilities (RCPs)

None of the above needs to be explicitly invoked by users, but they (or their symbolic links) should be placed in a *single* directory that enloc can access.


## Data preparation for ```enloc``` analysis


### Molecular QTL Data

```enloc``` requires summary information from the molecular QTL analysis to impute binary annotations (i.e. the latent true association status of each SNP with respect to the molecular phenotype) in enrichment analysis. These summary information details all possible association models (i.e., combination of associated SNPs) and their assessed probabilities for each molecular trait.  This information can be obtained from Bayesian multi-SNP QTL analysis implemented in the software package ```dap```.

A sample set of eQTL annotation data from the cis-eQTL analysis of GTEx whole blood samples (version 6 release) can be downloaded [here](http://www-personal.umich.edu/~xwen/download/gtex_whole_blood.v6.tgz).
The data set contains fine-mapping result of cis-eQTLs from 22,749 genes analyzed by the greedy version of the DAP algorithm.
We also provide a wiki page on the complete flow of Bayesian molecular QTL analysis.


### GWAS Data

The default option for GWAS data is to utilize only the single-SNP testing summary statistics, namely the z-scores for each candidate SNPs. All the input data for a given GWAS trait should be organized into a single gzipped text file with the following simple format

```
   chr1:998395   Loc1  -0.178471
   chr1:1000156  Loc1  -0.169669
   chr1:1001177  Loc1  -0.247359
   chr1:1002932  Loc1  -0.240580
   chr1:1003629  Loc1  -0.169000
   chr1:1004957  Loc1  -1.145393
   chr1:1004980  Loc1  -1.145393
   chr1:1006223  Loc1  -1.174756
```
The first and second columns represent the ID the LD block of the corresponding SNP, respectively. The last column indicates the z-scores. The LD blocks are defined based on the results of [Berisa and Pickrell, 2015](http://bioinformatics.oxfordjournals.org/content/32/2/283). The segmentation of the LD blocks are population-specific, the detailed information can be found [here](https://bitbucket.org/nygcresearch/ldetect-data).

For reference, we provide a complete sample data from the GWAS of high density cholesterol (HDL): [HDL.z_score.gz](http://www-personal.umich.edu/~xwen/download/gwas_hdl/HDL.z_score.gz). The data set is orignially from [Teslovich (2010)](https://www.ncbi.nlm.nih.gov/pubmed/20686565) with additional 1000Genome SNPs imputed by [Pickrell (2014)](https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3980523/).



## Parameter file for enloc


## Running enloc


## Getting results



