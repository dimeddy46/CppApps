# cppApps
To download one folder(project) with git:<br><br>
set folder=[setThis] &<br>mkdir %folder% & cd %folder% & git init & git remote add origin https://github.com/dimeddy46/cppApps.git &<br> git config core.sparseCheckout true & echo %folder%/* > .git/info/sparse-checkout & <br> git fetch origin & git checkout origin/master
