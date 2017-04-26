
#pragma once
#include "application.h" // Required for Particle.

String uint8_vector_to_string_asci(std::vector<uint8_t> vec){
    String rv;
    rv.reserve(vec.size()+1);
    for( const auto &c : vec ){
        rv += char(c);
    }
    return rv;
}

String uint8_vector_to_string_hex( std::vector<uint8_t> vec ){
    String rv;
    rv.reserve(3*(vec.size())+1);
    for( const auto &hexbyte : vec ){
        rv += String::format("%02x ", hexbyte);
    }
    return rv;
}

int string_to_vector( String str, std::vector<uint8_t> v){
    v.clear();
    v.resize(str.length()+1);
    str.getBytes(this->v.data(), str.length()+1);
    this->PUB_asci();
    return this->v.size();
}

