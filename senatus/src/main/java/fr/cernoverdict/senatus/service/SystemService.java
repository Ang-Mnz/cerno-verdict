
package fr.cernoverdict.senatus.service;

import org.springframework.stereotype.Service;

import fr.cernoverdict.senatus.dto.SystemStatusResponse;
import fr.cernoverdict.senatus.dto.SystemStatusResponse.ComponentStatus;

@Service
public class SystemService {

    private final PraetoriumService praetoriumService;

    public SystemService(PraetoriumService praetoriumService) {
        this.praetoriumService = praetoriumService;
    }

    public SystemStatusResponse getSystemStatus() {
        return new SystemStatusResponse(
            new ComponentStatus(praetoriumService.getStatus()),
            new ComponentStatus("UNKNOWN"),
            new ComponentStatus("ONLINE")
        );
    }
}
