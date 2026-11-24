
package fr.cernoverdict.senatus.client;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestClient;

import fr.cernoverdict.senatus.dto.HealthResponse;

@Component
public class PraetoriumClient {

    private final RestClient restClient;

    public PraetoriumClient(
        @Value("${praetorium.base-url}") String baseUrl
    ) {
        this.restClient = RestClient.create(baseUrl);
    }

    public HealthResponse getHealth() {
        return restClient.get()
            .uri("/health")
            .retrieve()
            .body(HealthResponse.class);
    }
}
