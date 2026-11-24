package fr.cernoverdict.senatus.dto;

import com.fasterxml.jackson.annotation.JsonProperty;

public class HealthResponse {

    @JsonProperty("component")
    private String name;

    private String status;

    public HealthResponse(String name, String status) {
        this.name = name;
        this.status = status;
    }

    public String getName() {
        return name;
    }

    public String getStatus() {
        return status;
    }
}
