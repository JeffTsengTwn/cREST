# Redfish APP
A Redfish API implementation based on the cREST framework.

[Redfish](https://www.dmtf.org/standards/redfish) is a DMTF standard RESTful API for server and infrastructure management (BMC).

## Build and install
Make sure the cREST library is built and installed first.
```bash
cd apps/redfish
make clean
make all
sudo make install
```

## Run
```bash
lighttpd -D -f apps/redfish/lighttpd.conf
```

## API Endpoints
| Method | URI | Description |
|--------|-----|-------------|
| GET | `/redfish` | Redfish version |
| GET | `/redfish/v1` | Service Root |
| GET | `/redfish/v1/Systems` | Computer System Collection |
| GET | `/redfish/v1/Systems/1` | Computer System Instance |
| GET | `/redfish/v1/Chassis` | Chassis Collection |
| GET | `/redfish/v1/Chassis/1` | Chassis Instance |
| GET | `/redfish/v1/Managers` | Manager Collection |
| GET | `/redfish/v1/Managers/1` | Manager Instance (BMC) |
| GET | `/redfish/v1/AccountService` | Account Service |
| GET | `/redfish/v1/SessionService` | Session Service |

## Example
```bash
# Get Redfish version
curl http://127.0.0.1:8080/redfish

# Get Service Root
curl http://127.0.0.1:8080/redfish/v1

# Get Systems
curl http://127.0.0.1:8080/redfish/v1/Systems

# Get System details
curl http://127.0.0.1:8080/redfish/v1/Systems/1

# Get Chassis
curl http://127.0.0.1:8080/redfish/v1/Chassis/1

# Get Manager (BMC)
curl http://127.0.0.1:8080/redfish/v1/Managers/1
```

## Architecture
```
redfish/
├── main.c               # FastCGI entry point, controller registration
├── redfish_handler.h     # Handler declarations
├── redfish_handler.c     # Redfish endpoint implementations
├── Makefile
└── lighttpd.conf         # lighttpd server configuration
```

### Resource Hierarchy
```
/redfish
└── /v1                          (Service Root)
    ├── /Systems                  (Computer System Collection)
    │   └── /1                    (Computer System Instance)
    ├── /Chassis                  (Chassis Collection)
    │   └── /1                    (Chassis Instance)
    ├── /Managers                 (Manager Collection)
    │   └── /1                    (BMC Instance)
    ├── /AccountService           (Account Service)
    └── /SessionService           (Session Service)
```
