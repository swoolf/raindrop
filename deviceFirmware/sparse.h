#include <HttpClient.h>

String getName(int zipI){
    String zip;
    if (zipI==-1){ zip = "02139"; Serial.println("here-1");}
    else{zip = String(zipI); }

    for (int i=0; i< 5-zip.length(); i++){
        zip = "0"+ zip;
    }
    HttpClient http;


    http_header_t headers[] = {
        { NULL, NULL }
    };

    http_request_t request;
    http_response_t response;

    request.hostname = "somesite.azurewebsites.net";
    request.port = 80;
    request.path ="/api/HttpTriggerJS1?code=someCode/0yIlRdQoQ==&zip=" + zip;

    http.get(request, response, headers);
    Serial.println(zip);
    Serial.println(response.body);
    return(response.body);
}

void eParse(int intensity[], const char *data){
    char copyStr[256];
    String sdata = data;
    sdata.toCharArray(copyStr,256);
    char *p = strtok(copyStr, ",");

    for (int i =0; i<61; i++){
        intensity[i]=atoi(p);
        p = strtok(NULL,",");
        Serial.print(intensity[i]);
        }
}
