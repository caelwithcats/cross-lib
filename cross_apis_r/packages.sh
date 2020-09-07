actionsBuild=$1
# The following packages are required for crossLib:
if [ $actionsBuild == "true" ]
then
  sudo apt-get update
  sudo apt-get -y install libgtk-3-dev mingw-w64 g++ gcc build-essential libx11-dev
else
  sudo apt-get update
  sudo apt-get install mingw-w64 g++ gcc build-essential libx11-dev
fi

# For 32-bit support
#sudo apt-get install g++-multilib libgdk-pixbuf2.0-dev:i386 libicu-dev:i386 libharfbuzz-dev:i386 libpango1.0-dev:i386

# Optinal:
# Good for testing windows .EXE files
if [ $actionsBuild == "true" ]
then
  echo "Done."
else
  read -p "Would you like to  install wine? Continue (y/n)?" choice
  case "$choice" in 
    y|Y ) echo Updating...; sudo apt update; echo "You should now be able to install WINE from the software centre (mintinstall if you are using linux mint)";; 
    n|N ) echo "no";;
    * ) echo "invalid answer";;
  esac
fi
