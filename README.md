# ENLOC: Enichment Estimation Aided Colocalization Analysis



This repository contains the software implementation of *enloc*, which enables integrative genetic association analysis of molecular QTL data and GWAS data. The statistical model and the key computational procedures are described in this [manuscript](http://biorxiv.org/content/early/2016/10/02/078667).

For questions/comments regarding to the software package, please contact Xiaoquan Wen (xwen at umich dot edu).



## License

Software distributed under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version. See [LICENSE](http://www.gnu.org/licenses/gpl-3.0.en.html) for more details.


## Repository structure

* ``src``: the directory contains scripts for the software pipeline and relevant instructions
* ``examples``: sample data and a step-by-step guide for reproducing the analysis described in the manuscript





## Dependency 

The softwar pipeline assumes the availability of the following executables

*  [perl](https://www.perl.org/get.html)
*  [torus](https://github.com/xqwen/dap/tree/master/torus_src)
*  [dap](https://github.com/xqwen/dap/)
*  [openmp_wrapper](https://github.com/xqwen/openmp_wrapper)


## Molecular QTL data analysis

Enloc also requires specific (Bayesian) analysis of molecular QTL data, which can be achieved by the ```dap``` and ```torus```. A detailed [step-by-step guideline](https://xqwen.github.io/qtl_pipeline/) with real data is provided.  



## Citation

* Wen, X., Pique-Regi, R., Luca, F. Integrating Molecular QTL Data into Genome-wide Genetic Association Analysis: Probabilistic Assessment of Enrichment and Colocalization. *PLOS Genetics*. 2017 Mar 13(3): e1006646. 