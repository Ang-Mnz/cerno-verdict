package fr.cernoverdict.senatus.dto;

public record SystemStatusResponse(
    ComponentStatus praetorium,
    ComponentStatus vigile,
    ComponentStatus senatus
) {
    public record ComponentStatus(String status) {}
}
