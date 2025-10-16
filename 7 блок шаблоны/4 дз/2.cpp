#include <fstream>
#include <memory>
#include <stdexcept>

class HTMLFormattable {
public:
    virtual ~HTMLFormattable() = default;
    virtual std::string toHTML() const = 0;
};

class TextFormattable {
public:
    virtual ~TextFormattable() = default;
    virtual std::string toText() const = 0;
};

class JSONFormattable {
public:
    virtual ~JSONFormattable() = default;
    virtual std::string toJSON() const = 0;
};

class Data {
public:
    explicit Data(std::string data) : data_(std::move(data)) {}
    virtual ~Data() = default;
    
    const std::string& getContent() const { return data_; }

private:
    std::string data_;
};

class HTMLFormatter {
public:
    std::string format(const Data& data) const {
        return "<html>" + data.getContent() + "</html>";
    }
};

class TextFormatter {
public:
    std::string format(const Data& data) const {
        return data.getContent();
    }
};

class JSONFormatter {
public:
    std::string format(const Data& data) const {
        return "{ \"data\": \"" + data.getContent() + "\"}";
    }
};

class UniversalData : public Data, public HTMLFormattable, public TextFormattable, public JSONFormattable {
public:
    explicit UniversalData(std::string data) : Data(std::move(data)) {}
    
    std::string toHTML() const override {
        HTMLFormatter formatter;
        return formatter.format(*this);
    }
    
    std::string toText() const override {
        TextFormatter formatter;
        return formatter.format(*this);
    }
    
    std::string toJSON() const override {
        JSONFormatter formatter;
        return formatter.format(*this);
    }
};

class DataSaver {
public:
    virtual ~DataSaver() = default;
    virtual void save(std::ofstream& file, const Data& data) const = 0;
};

class HTMLSaver : public DataSaver {
public:
    void save(std::ofstream& file, const Data& data) const override {
        HTMLFormatter formatter;
        file << formatter.format(data);
    }
};

class TextSaver : public DataSaver {
public:
    void save(std::ofstream& file, const Data& data) const override {
        TextFormatter formatter;
        file << formatter.format(data);
    }
};

class JSONSaver : public DataSaver {
public:
    void save(std::ofstream& file, const Data& data) const override {
        JSONFormatter formatter;
        file << formatter.format(data);
    }
};

class SaverFactory {
public:
    static std::unique_ptr<DataSaver> createHTMLSaver() {
        return std::make_unique<HTMLSaver>();
    }
    
    static std::unique_ptr<DataSaver> createTextSaver() {
        return std::make_unique<TextSaver>();
    }
    
    static std::unique_ptr<DataSaver> createJSONSaver() {
        return std::make_unique<JSONSaver>();
    }
};

void saveTo(std::ofstream& file, const Data& data, const DataSaver& saver) {
    saver.save(file, data);
}

void saveToAsHTML(std::ofstream& file, const Data& data) {
    HTMLSaver saver;
    saveTo(file, data, saver);
}

void saveToAsJSON(std::ofstream& file, const Data& data) {
    JSONSaver saver;
    saveTo(file, data, saver);
}

void saveToAsText(std::ofstream& file, const Data& data) {
    TextSaver saver;
    saveTo(file, data, saver);
}

void saveFormattableToHTML(std::ofstream& file, const HTMLFormattable& formattable) {
    file << formattable.toHTML();
}

void saveFormattableToJSON(std::ofstream& file, const JSONFormattable& formattable) {
    file << formattable.toJSON();
}

void saveFormattableToText(std::ofstream& file, const TextFormattable& formattable) {
    file << formattable.toText();
}