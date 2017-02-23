# Instructions for enloc

```enloc``` implements the analysis pipeline for enrichment estimation aided colocalization analysis.

## Prerequisite and installation

The single execution point to carry out the full integrative analysis is the perl script ```enloc```, which assumes a few scripts and binary executables pre-installed in the running machine.

* ```torus```: binary executable to carry out the EM algorithm for enrichment estimation. ([repo](https://github.com/xqwen/dap/tree/master/torus_src))
*  ```openmp_wrapper```: binary executable to carry out multi-thread batch processing ([repo](https://github.com/xqwen/openmp_wrapper))
* ```mi_eqtl```: perl script to sample multiple imputation QTL data sets (available in this directory)
* ```get_pip```: perl script to collect QTL posterior inclusion probabilities (PIPs) from QTL analysis results
* ```compute_rcp```: perl script to compute regional colocalization probabilities (RCPs)

None of the above needs to be explicitly invoked by users, but they (or their symbolic links) should be placed in a single directory that enloc can access.





## Data preparation for enloc analysis



