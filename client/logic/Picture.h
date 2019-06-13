//
// Created by kevin on 12/06/19.
//

#ifndef MYINVINCIBLELIBRARY_PICTURE_H
#define MYINVINCIBLELIBRARY_PICTURE_H

#include <string>

using namespace std;

class Picture {

public:

    Picture() = default;

    Picture(string name, string author, int year, string pictureData){
        this->name = name;
        this->author = author;
        this->year = year;
        this->pictureData = pictureData;
        this->size = 0;
        this->id = 0;
    }

    const string &getName() const;
    void setName(const string &name);
    const string &getAuthor() const;
    void setAuthor(const string &author);
    int getYear() const;
    void setYear(int year);
    int getSize() const;
    void setSize(int size);
    const string &getPictureData() const;
    void setPictureData(const string &pictureData);
    int getId() const;
    void setId(int id);
    string serialize();
    void deserialize(string jsonPicture);

private:

    string name;
    string author;
    int year;
    int size;
    string pictureData;
    int id;

};


#endif //MYINVINCIBLELIBRARY_PICTURE_H
