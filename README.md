# Minecamp
## ZPR Project

###### W celu uruchomienia aplikacji należy:

1. Pobrać oraz zainstalować biblioteke [openFrameworks](http://openframeworks.cc/) 
2. Następnie należy umieścić folder z aplikacją w katalogu z biblioteką: /apps/myApps
3. Uruchomić skrypt budujący
4. Plik wykonywalny znajdować się będzie w folderze /bin

###### W celu uruchomienia testów należy:
1. W pliku config.make, w sekcji PROJECT EXCLUSIONS zakomentować linię `PROJECT_EXCLUSIONS += $(PROJECT_ROOT)/tests`oraz odkomentować linię `PROJECT_EXCLUSIONS += $(PROJECT_ROOT)/src/App`
2. W tym samym pliku w sekcji PROJECT DEFINES odkomentować obie linie

