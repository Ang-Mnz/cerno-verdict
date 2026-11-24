package fr.cernoverdict.senatus.dto;

public class HealthResponse {

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
