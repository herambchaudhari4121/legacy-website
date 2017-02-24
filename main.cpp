#include <uWS/uWS.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

std::vector<std::string> storedMessages;
std::vector<int> excludedMessages;
std::stringstream indexHtml;
std::string pidString;
int connections = 0;
char line[1024];

int getKb() {
    FILE *pipe = popen(("pmap " + pidString + " | tail -1").c_str(), "r");
    fgets(line, sizeof(line), pipe);
    pclose(pipe);
    unsigned long kbUsage = atoi(strrchr(line, ' '));
}

int main() {
    uWS::Hub h;

    pidString = std::to_string(::getpid());

    std::cout << "pid: " << pidString << std::endl;

    indexHtml << std::ifstream ("index.html").rdbuf();
    if (!indexHtml.str().length()) {
        std::cerr << "Failed to load index.html" << std::endl;
        return -1;
    }

    h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
        if (req.getUrl().valueLength == 1) {
            res->end(indexHtml.str().data(), indexHtml.str().length());
        } else {
            // i guess this should be done more gracefully?
            res->end(nullptr, 0);
        }
    });

    h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
        // send this client all stored messages in one batch send
        uWS::WebSocket<uWS::SERVER>::PreparedMessage *preparedMessageBatch = uWS::WebSocket<uWS::SERVER>::prepareMessageBatch(storedMessages, excludedMessages, uWS::TEXT, false);
        ws.sendPrepared(preparedMessageBatch);
        ws.finalizeMessage(preparedMessageBatch);

        // broadcast number of clients connected to everyone
        std::string tmp = "S " + std::to_string(++connections) + " " +  std::to_string(getKb());
        h.getDefaultGroup<uWS::SERVER>().broadcast(tmp.data(), tmp.length(), uWS::TEXT);
    });

    h.onMessage([&h](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
        if (length && data[0] != 'S' && length < 4096) {
            // add this message to the store, cut off old messages
            if (storedMessages.size() == 50) {
                storedMessages.erase(storedMessages.begin());
            }
            storedMessages.push_back(std::string(data, length));
            //std::cout << "Message posted: " << storedMessages.back() << std::endl;

            // simply broadcast this message to everyone (completely without any timeout optimization!)
            h.getDefaultGroup<uWS::SERVER>().broadcast(data, length, uWS::TEXT);
        }
    });

    h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
        // broadcast number of clients connected to everyone
        std::string tmp = "S " + std::to_string(--connections) + " " +  std::to_string(getKb());
        h.getDefaultGroup<uWS::SERVER>().broadcast(tmp.data(), tmp.length(), uWS::TEXT);
    });

    h.getDefaultGroup<uWS::SERVER>().startAutoPing(30000);
    if (h.listen(3000)) {
        std::cout << "Listening to port 3000" << std::endl;
    } else {
        std::cerr << "Failed to listen to port" << std::endl;
        return -1;
    }
    h.run();
}
