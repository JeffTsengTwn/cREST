# cREST
This is a simple RESTful API framework base on CGI.
You can run it with lighttpd + FastCGI.

## Build and install cREST library
```bash
make clean
make all
sudo make uninstall
sudo make install
```

## Prerequisites
1. Install dependency packages for compiling lighttpd.
```bash
sudo apt-get install autoconf
sudo apt-get install automake
sudo apt-get install libtool
sudo apt-get install m4
sudo apt-get install pkg-config
sudo apt-get install libpcre2-dev
sudo apt-get install zlib1g-dev
```
2. Checkout lighttpd source code.
```bash
git clone https://git.lighttpd.net/lighttpd/lighttpd1.4.git
cd lighttpd1.4
git pull
```
3. Build and install lighttpd.
```bash
cd lighttpd1.4
./autogen.sh
./configure -C --prefix=/usr/local
make -j 4
make check
sudo make install
```
4. Install dependency packages for compiling FastCGI.
```bash
sudo apt-get install gcc make m4 autoconf automake libtool
```
5. Checkout FastCGI source code.
```bash
git clone https://github.com/FastCGI-Archives/fcgi2.git
```
6. Build and install FastCGI.
```bash
cd fcgi2
./autogen.sh
./configure
make
make install
```

## Apps

All applications are located under the `apps/` directory.

### Example APP (Hello World)
```bash
cd apps/example
make clean
make all
sudo make install
```
Run with lighttpd:
```bash
lighttpd -D -f apps/example/lighttpd.conf
```
Visit http://127.0.0.1:8080/rest/hello

### Redfish APP
See [apps/redfish/README.md](apps/redfish/README.md) for details.
