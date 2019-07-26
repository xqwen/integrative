## Required input

The required input files are 

1. GWAS summary statistics: a text file 
2. Multi-SNP analysis results of molecular QTL mapping by DAP-G: a directory 
3. Summarized SNP-level PIP information from DAP-G results: a text file
4. Summarized signal-cluster information from DAP-G results: a text file 

Note that the last two files can be generated from 2, specially through the perl scripts provided in the ``utility`` directory. e.g.

```
perl get_max_pip.pl eqtl_dir > pip.info
perl summarize_dapg_sig.pl eqtl_dir > eqtl.sig.summary
```

Also, if the user is only interested in enrichment analysis, the last two files can be ignored.  


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


## Required utilities

### Executables for analysis

The following executables are required for performing enloc analysis. They (or their soft links) should be placed in the ``bin_dir`` specified in the enloc parameter file.

+ ``mi_eqtl`` (perl script, unchanged from version 1)
+ ``torus`` (binary executable, unchanged from version 1)
+ ``prep_enloc_dap1`` (perl script, new to this version)
+ ``enloc_dap1`` (binary executable, new to this version)
+ ``prep_rcp`` (perl script, new to this version)
+ ``compute_rcp`` (binary executable, new to this version)

 
### Executables for batch processing

The modified pipeline now only generates batch command files, which need to be executed manually by users. This feature provides users flexibility of selecting the running environment.

#### Option 1: run as shell scripts

This option requires to additional utility, one can simply run the generated batch command file as a shell script. This is probably the simplest solution, but is also the most inefficient one. 

#### Option 2: run on a multi-core workstation

We recommend (``openmp_wrapper``)[] in this setting, which allows a specified number of commands to be processed in parallel.

#### Option 3: run in a cluster environment

We provide an example utility ``qsub_wrapper`` to submit jobs specified in batch command files. 



## Parameter file for enloc

Parameters required by the integrative analysis are supplied through a single text file. An example of the parameter file is provided [here](../examples/HDL_blood.enloc.params). The informative line of the parameter file has the following format
```
KEYWORD   VALUE
```
The keywords are case-insensitive. Comments line are allowed in the parameter file by annotating a ```#``` at the beginning of the comment.

The required parameters by ``enloc_enrich`` include:

+ **BIN_DIR**: all previously listed analysis utilities (``mi_eqtl``,``torus``, ``enloc_dap1``, ``prep_rcp``, ``compute_rcp``) should be  accessed from a single directory, and BIN_DIR specifies the location of this directory containing all the utilities. Users can make symbolic links to  BIN_DIR instead of copying the executables. Relative path is allowed.
+ **GWAS_DATA**: location of the gzipped GWAS z-score file. Relative path is allowed.
+ **QTL_FM_DIR**: location of the directory containing fine-mapping results of molecular QTL analysis. Relative path is allowed.
+ **OUT_DIR**: output (and working) directory name. enloc will create the directory if it does not already exist. Relative path is allowed.
+ **TRAIT**: the name of the GWAS trait

The ***additional*** required parameters by ``enloc_rcp`` include:


+ **QTL_PIP**: SNP-level pip file from eQTL analysis by DAP-G
+ **QTL_SUMMARY**: signal-level summary from eQTL analysis by DAP-G



## Analysis procedure


### Step 1: prepare input 

Make sure the required input data, analysis utilities and the parameter file are in place.


### Step 2: enrichment analysis

The command for generating the scripts of enrichment analysis is 

```
enloc_enrich param_file
```

Upon successful execution, two scripts ``prep_mi.cmd`` and ``mi.cmd`` are generated in the specified ``out_dir`` by the parameter file.


### Step 3: colocalization analysis

Once the enrichment analysis is complete, one can use the following command to generate the script for colocalization analysis: 

```
enloc_rcp param_file
```

A single script named ``rcp.cmd`` will be generated in the ``out_dir`` upon successful execution.

### Step 4: getting output

#### The enrichment analysis output

This file is named ```TRAIT_NAME.enrich.est```. It summarizes the enrichment estimation from multiple imputations. An example output is given below

```
 -10.380    -10.435    -10.324
  4.759      3.098      6.421
 ```
   
The first line indicate the estimate of the intercept term (first column) and its 95\% confidence interval (second and third column). The second line represents the enrichment estimate in log-odds ratio (first column) and its corresponding 95\% confidence interval (second and third column).

#### The colocalization analysis output

The results of colocalization analysis are summarized in the file```TRAIT_NAME.enloc.out``. The col
umns of this file are
```
eqtl_locus   cum_eqtl_pip    cum_gwas_pip   num_of_snps   rcp   lead_coloc_SNP  lead_snp_scp
```
Specifically,  ``eqtl_locus`` indicates the eQTL locus name;``cum_eqtl_pip`` and ``cum_gwas_pip``represent the cumulative posterior inclusion probabilities (PIPs) of the locus containing a causal eQTL and a causal GWAS hit, respectively; ``num_of_snps`` indicates number of member SNPs (in LD) within the locus;``rcp`` reprsents the regional colocalization probability of the locus The entry ```lead_coloc_SNP``` provides the lead SNP with highest SNP-level colocalization probability whose exact value is shown in the entry ```lead_snp_scp```.

An example output is shown below
```
ENSG00000163704.11:1    0.987   1.000     1   9.996e-01  chr3_9933702_C_G_b38 9.996e-01
 ENSG00000230082.1:1    0.900   1.000     1   9.971e-01  chr3_9933702_C_G_b38 9.971e-01
ENSG00000117122.13:1    0.994   1.000     9   9.530e-01  chr1_16980180_C_G_b38 9.530e-01
ENSG00000089101.17:1    0.998   0.994     3   9.447e-01  chr20_20087991_C_G_b38 9.068e-01
```
The entries are sorted according to the descending order of their rcp values.

