# Samvaad-Hindi-English-Speech-Translation
This project is a **console-based application** that converts **spoken Hindi input** into **English text output**.  
It was created using **Visual C++ AppWizard** and extended with speech recognition and translation logic.  

---

## Project Structure  

- **Hindi_to_english_translation.vcxproj**  
  Main project configuration file (Visual Studio). Stores project settings, platform info, and compiler options.  

- **Hindi_to_english_translation.vcxproj.filters**  
  Organizes source, header, and resource files in Visual Studio.  

- **Hindi_to_english_translation.cpp**  
  Core application file implementing speech recognition and translation pipeline.  

- **StdAfx.h / StdAfx.cpp**  
  Precompiled header files to speed up compilation.  

---

## Features  

- Captures **Hindi speech** using a microphone.  
- Converts speech to **Hindi text** (speech recognition).  
- Translates Hindi text to **English text** (translation engine).  
- Displays English translation directly in the **console**.  
- Lightweight and modular design for easy extension.  

---

## How to Build & Run  

1. Open the project in **Visual Studio**.  
2. Build the solution (`Ctrl + Shift + B`).  
3. Connect a **microphone**.  
4. Run the executable and start speaking in **Hindi**.  
5. The application prints the **English text translation** in the console.  

---

## 📌 Future Enhancements  

- Add **Text-to-Speech (TTS)** for spoken English output.  
- Enable **real-time speech-to-text subtitles**.  
- Extend support for **other Indian languages**.  
- Integrate with cloud APIs (Google Speech, Azure, or OpenAI Whisper) for higher accuracy.  

---

## 📜 Notes  

- AppWizard-generated comments (`TODO:` markers) remain in the source to guide customization.  
- This project demonstrates integration of **speech recognition** and **language translation** in C++.  
- Can be extended into GUI-based or mobile applications.  

---

## 🎯 Example (Demo)  

**Input (spoken in Hindi):**  
