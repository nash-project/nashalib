#include <nashalib/bencoder.hpp>
#include <stdio.h>
#include <nashalib/Data.hpp>
#include <string.h>
namespace nashalib{

void BEncoder::add_byte(unsigned char byte){
	fwrite(&byte, sizeof(unsigned char), 1, ofile);
    cpos++;
    //printf("%02x ",byte);
}

void BEncoder::add_int(int number, int endianess){
    (void)endianess;
	fwrite(&number, sizeof(int), 1, ofile);
    cpos += 4;
    //printf("%08x ", number);
}

void BEncoder::add_short(int number, int endianess){
    (void)endianess;
	fwrite(&number, sizeof(short), 1, ofile);
    cpos += 2;
    //printf("%04x ", number);
}

void BEncoder::add_imm(int value, int size, int endianess){
    (void)endianess;

    switch (size){
        case 32:
        {
            add_int(value, endianess);
            break;
        }
        case 16:
            add_short(value, endianess);
            break;
        case 8:
            add_byte(value);
            break;
    }
}

void BEncoder::add_label(std::string label, bool relative){
    struct label_map_entry * entry = NULL;
    entry = (struct label_map_entry*)malloc(sizeof(struct label_map_entry));
    entry->pos = cpos;
    entry->relative = relative;
    entry->label = new char[label.size()+1];
    strcpy(entry->label, label.c_str());
    referenced_labels_map.push_back(entry);
    add_imm(0, 32, ENDIANESS__BIG_ENDIAN__); // can be zero because it will be set later
}


Label* BEncoder::_add_label(std::string label, int vis, section s){
    if (s == section::_text){
        Label * label_ = new Label(cpos, vis, s);
        labels.insert({label, label_});
        return label_;
    }
    else if (s == section::_data){
        Label * label_ = new Label(data_cpos, vis, s);
        labels.insert({label, label_});
        return label_;
    }

    return NULL;
}

int BEncoder::_get_label(std::string label){
    return labels[label]->offset;
}

int BEncoder::_get_cpos(){
    return cpos;
}

Label * BEncoder::_get_label_obj(std::string label){
    return labels[label];
}
void BEncoder::_add_data( Data * _data){
    data.push_back(_data);
    data_cpos += _data->size;
}

int BEncoder::_get_data_cpos(){
    return data_cpos;
}

void BEncoder::_resolve_labels(){
    int pos = 0;
    for (auto label: referenced_labels_map){
        auto label_obj = labels[label->label];
        //printf("label_p_address->[%d]; label_imm_pos->[%d]; label_identifier->[%s]\n", label_obj->offset, label->pos, label->label);

        if (label_obj->_section != section::_text){
            relocation_entry * entry = new relocation_entry(label_obj->_section, label->pos);
            reloctable_table.push_back(entry);

            fseek(ofile, label->pos, SEEK_SET);
            fwrite(&label_obj->offset, sizeof(int), 1, ofile);
        }
        else{
            if (label->relative){
                pos = label_obj->offset - (label->pos+sizeof(int));
            }
            else{
                pos = label_obj->offset;
            }
            fseek(ofile, label->pos, SEEK_SET);
            fwrite(&pos, sizeof(int), 1, ofile);
        }
        
    }
}

}