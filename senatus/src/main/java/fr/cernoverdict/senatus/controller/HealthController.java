package fr.cernoverdict.senatus.controller;

import fr.cernoverdict.senatus.dto.HealthResponse;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class HealthController {

    @GetMapping("/health")
    public HealthResponse health() {
        return new HealthResponse("Senatus", "UP");
    }

}
