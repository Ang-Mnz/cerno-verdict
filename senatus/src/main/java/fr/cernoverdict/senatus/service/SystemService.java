package fr.cernoverdict.senatus.service;

import org.springframework.stereotype.Service;

import fr.cernoverdict.senatus.dto.SystemStatusResponse;
import fr.cernoverdict.senatus.dto.SystemStatusResponse.ComponentStatus;

@Service
public class SystemService {

    public SystemStatusResponse getSystemStatus() {
        return new SystemStatusResponse(
            new ComponentStatus("ONLINE"),
            new ComponentStatus("ONLINE"),
            new ComponentStatus("ONLINE")
        );
    }
}
