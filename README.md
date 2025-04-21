### Weighted Satisfiability Problem of Boolean CNF with Maximal Ones

The aim of this project is to solve the Maximum Weighted Satisfiability Problem (MWSAT)
for a Boolean CNF formula using an advanced iterative method, specifically simulated annealing.  
More detailed explanation, solution steps and results (white/black box analysis and more)
can be found in the `report.pdf` file.

The code is in the file `mwsat`, and can be compiled using the provided `Makefile`.  
To run the program, use the format: `./mwsat input_file.mwcnf`, where the input is in MWCNF format (an extension of DIMACS with added weights).

The output files will have the same name as the input, but with `.dat` extension, and will be saved inside the `out` folder.

The results were analyzed using the Jupyter notebook: `jupyter/sample.ipynb`.

The project is documented using `Doxygen`. Generate the documentation: `doxygen Doxyfile`.
