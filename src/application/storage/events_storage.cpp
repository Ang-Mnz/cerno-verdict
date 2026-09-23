#include <filesystem>
#include <iostream>

#include "events_storage.hpp"

EventStorage::EventStorage()
{
}

bool EventStorage::save(const MotionEvent& event)
{
    std::time_t time =
        std::chrono::system_clock::to_time_t(event.timestamp());

    std::tm local_time{};

    localtime_r(&time, &local_time);

    std::ostringstream date;

    date << std::put_time(&local_time, "%Y-%m-%d");

    std::filesystem::path directory =
        std::filesystem::path(config_.path_events) / date.str();

    try
    {
        std::filesystem::create_directories(directory);
    }
    catch (const std::filesystem::filesystem_error& error)
    {
        std::cerr << "Erreur création dossier : "
                  << error.what()
                  << std::endl;

        return false;
    }


    std::filesystem::path path =
        directory / event.image_filename();

	if (!event.save_image(path.string()))
    {
        return false;
    }

	// Test du nombre d'images
    enforce_limit();

    return true;
}

void EventStorage::enforce_limit()
{
    try
    {
        std::vector<std::filesystem::path> images;

        // Itération récursive dans le dossier pour récupérer le nombre d'images et leur chemins.
        for (const auto& entry :
             std::filesystem::recursive_directory_iterator(config_.path_events))
        {
            if (!entry.is_regular_file())
            {
                continue;
            }

            if (entry.path().extension() == ".jpg")
            {
                images.push_back(entry.path());
            }
        }

        // Si nombre max d'images pas atteint
        if (images.size() <= config_.max_images)
        {
            return;
        }

        // trie des images dans l'ordre de la plus ancienne à la plus récente
        std::sort(
            images.begin(),
            images.end(),
            [](const std::filesystem::path& a,
               const std::filesystem::path& b)
            {
                return std::filesystem::last_write_time(a) <
                       std::filesystem::last_write_time(b);
            }
        );

        // Suppression des images
        while (images.size() > config_.max_images)
        {
            std::filesystem::remove(images.front());
            images.erase(images.begin());
        }

        // Suppression des dossiers vides
        for (const auto& entry :
             std::filesystem::directory_iterator(config_.path_events))
        {
            if (entry.is_directory() &&
                std::filesystem::is_empty(entry.path()))
            {
                std::filesystem::remove(entry.path());
            }
        }
    }
    catch (const std::filesystem::filesystem_error& error)
    {
        std::cerr << "Erreur gestion du stockage : "
                  << error.what()
                  << std::endl;
    }
}
