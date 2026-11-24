package fr.cernoverdict.senatus.service;

import org.springframework.stereotype.Service;

import fr.cernoverdict.senatus.dto.SystemStatusResponse;
import fr.cernoverdict.senatus.dto.SystemStatusResponse.ComponentStatus;

@Service
public class SystemService {

    private final PraetoriumService praetoriumService;
    private final VigileService vigileService;

    public SystemService(
        PraetoriumService praetoriumService,
        VigileService vigileService
    ) {
        this.praetoriumService = praetoriumService;
        this.vigileService = vigileService;
    }

    public SystemStatusResponse getSystemStatus() {
        return new SystemStatusResponse(
            new ComponentStatus(praetoriumService.getStatus()),
            new ComponentStatus(vigileService.getStatus()),
            new ComponentStatus("ONLINE")
        );
    }
}
