# The following packages are required for crossLib:
sudo apt-get install mingw-w64 g++ gcc build-essential libx11-dev
# For 32-bit support
#sudo apt-get install g++-multilib libgdk-pixbuf2.0-dev:i386 libicu-dev:i386 libharfbuzz-dev:i386 libpango1.0-dev:i386

# Optinal:
# Good for testing windows .EXE files
read -p "Would you like to  install wine? Continue (y/n)?" choice
case "$choice" in 
  y|Y ) echo Updating...; sudo apt update; echo "You should now be able to install WINE from the software centre (mintinstall if you are using linux mint)" 
  n|N ) echo "no";;
  * ) echo "invalid answer";;
esac