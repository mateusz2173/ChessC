# ChessC  
  
Istrukcja kompilacji i uruchamiania:  
a) System zawiera zainstalowaną biblioteki allegro5:  
  
git clone https://github.com/mateusz2173/ChessC.git  
cd ChessC  
make  
make run  
  
b) System nie ma zainstalowanych bibliotek allegro5  
  
git clone https://github.com/mateusz2173/ChessC.git  
cd ChessC  
git clone https://github.com/liballeg/allegro5  
mkdir build  
cd build  
cmake ..  
mv SzachyC.exe ..  
cd ..  
./SzachyC.exe  
