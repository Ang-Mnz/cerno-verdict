
package fr.cernoverdict.senatus.service;

import org.springframework.stereotype.Service;
import org.springframework.web.client.RestClientException;

import fr.cernoverdict.senatus.client.PraetoriumClient;
import fr.cernoverdict.senatus.dto.HealthResponse;

@Service
public class PraetoriumService {

    private final PraetoriumClient praetoriumClient;

    public PraetoriumService(PraetoriumClient praetoriumClient) {
        this.praetoriumClient = praetoriumClient;
    }

    public String getStatus() {
        try {
            HealthResponse response = praetoriumClient.getHealth();

            if ("UP".equals(response.getStatus())) {
                return "ONLINE";
            }

            return "OFFLINE";
        }
        catch (RestClientException e) {
            return "OFFLINE";
        }
    }
}
