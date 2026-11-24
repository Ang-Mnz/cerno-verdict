package fr.cernoverdict.senatus.service;

import org.springframework.stereotype.Service;
import org.springframework.web.client.RestClientException;

import fr.cernoverdict.senatus.client.VigileClient;
import fr.cernoverdict.senatus.dto.HealthResponse;

@Service
public class VigileService {

    private final VigileClient vigileClient;

    public VigileService(VigileClient vigileClient) {
        this.vigileClient = vigileClient;
    }

    public String getStatus() {
        try {
            HealthResponse response = vigileClient.getHealth();

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
