
#pragma once
#include "application.h" // Required for Particle.
#include "HexString.h" // Required for Particle.

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

std::vector<uint8_t> string_to_vector( String str){
    std::vector<uint8_t> v;
    v.clear();
    v.resize(str.length()+1);
    str.getBytes(v.data(), str.length()+1);
    return v;
}

std::vector<uint8_t> string_toint_vector( String hex_string ){
    auto char_vec = string_to_vector(hex_string);
    auto hex_vec = std::vector<uint8_t>{};
    hex_vec.resize(2*char_vec.size());
    HexToBin ((char*)char_vec.data(), hex_vec.data(), char_vec.size());
    return hex_vec;
}

