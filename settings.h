// TODO: create an interface to change these

const char* ntpServerName = "europe.pool.ntp.org"; // NTP server hostname - see http://www.pool.ntp.org/en/vendors.html
#define NTP_INTERVAL 1024  // seconds between polling the NTP server - check with your ntp operator before lowering this

// TODO: more time zones
TimeChangeRule euCDT = {"ST", Last, dowSunday, Mar, 2, +120};
TimeChangeRule euCST = {"WT", Last, dowSunday, Oct, 2, +60};

Timezone euCT(euCDT, euCST);

#define TIMEZONE euCT
