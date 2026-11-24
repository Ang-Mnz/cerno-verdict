package fr.cernoverdict.senatus.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import fr.cernoverdict.senatus.dto.SystemStatusResponse;
import fr.cernoverdict.senatus.service.SystemService;

@RestController
@RequestMapping("/system")
public class SystemController {

    private final SystemService systemService;

    public SystemController(SystemService systemService) {
        this.systemService = systemService;
    }

    @GetMapping("/status")
    public SystemStatusResponse getSystemStatus() {
        return systemService.getSystemStatus();
    }
}
