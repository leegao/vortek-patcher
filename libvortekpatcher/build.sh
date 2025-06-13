mkdir -p build
cd build

if [ ! -f ~/Android/Sdk/ndk/27.0.12077973/build/cmake/android.toolchain.cmake ]; then
	echo "Make sure you have an Android SDK installed at ~/Android/Sdk (e.g. via Android Studio)"
	exit 1;
fi

cmake -DCMAKE_TOOLCHAIN_FILE=~/Android/Sdk/ndk/27.0.12077973/build/cmake/android.toolchain.cmake \
    -DANDROID_ABI=arm64-v8a \
    -DANDROID_PLATFORM=android-26 \
    -G Ninja ..

ninja