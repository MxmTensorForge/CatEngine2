#ifndef TEXTMANAGER_H
#define TEXTMANAGER_H

#include <unordered_map>
#include <memory>

#include "../UI/TextData.h"

class TextManager final
{
private:
    std::unordered_map<std::string, std::unique_ptr<TextData>> _textsData;
    
    TextManager() = default;
    ~TextManager() = default;
public:
    TextManager(const TextManager&) = delete;
    TextManager& operator=(const TextManager&) = delete;
    TextManager(TextManager&&) = delete;
    TextManager& operator=(TextManager&&) = delete;

    static TextManager& getInstance() noexcept {
        static TextManager manager;
        return manager;
    }

    void loadFromFile(const std::string& name, const std::string& fntPath, const std::string& texturePath) noexcept;
    const TextData* getTextData(const std::string& name) const noexcept;
};

#endif
