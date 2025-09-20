# Samvaad-Hindi-English-Speech-Translation
This project is a **console-based application** that converts **spoken Hindi words** into **English text**.  
It uses **audio signal processing**, **feature extraction**, and **Hidden Markov Models (HMM)** to recognize words from recorded Hindi speech and map them to their English equivalents.  

---

## Project Structure  

- **Hindi_to_english_translation.vcxproj**  
  Main Visual C++ project file containing configuration, platform info, and build settings.  

- **Hindi_to_english_translation.vcxproj.filters**  
  Organizes source and header files inside Visual Studio.  

- **Hindi_to_english_translation.cpp**  
  Core source code implementing:  
  - Audio recording and playback using Windows API  
  - Signal processing (DC shift, normalization, Hamming window)  
  - Feature extraction (autocorrelation, LPC, cepstral coefficients, raised sine)  
  - Codebook generation (LBG algorithm)  
  - HMM training and prediction  

- **StdAfx.h / StdAfx.cpp**  
  Precompiled headers to improve compilation speed.  

- **Output_Training/**  
  Contains generated **codebooks** and **universe CSV files** for HMM training.  

- **Trained_Model/**  
  Stores trained **HMM parameters (PI, A, B)** for each word.  

- **Hindi recording/**  
  Folder containing recorded Hindi word samples (`.txt` format) used for training and testing.  

---

## Features  

- Records **Hindi speech** through a microphone.  
- Processes the audio: DC shift, normalization, windowing, and feature extraction.  
- Generates a **codebook** using the LBG algorithm for vector quantization.  
- Trains **Hidden Markov Models (HMMs)** for each word based on training samples.  
- Predicts **English translation** of spoken Hindi words.  
- Provides **live testing** and **pre-recorded sample testing**.  

---

## How to Build & Run  

1. Open the project in **Visual Studio**.  
2. Build the solution (`Ctrl + Shift + B`).  
3. Connect a **microphone** for live testing.  
4. Run the executable:  
   - **Training:** Generates universe, codebook, and trains HMMs from recorded Hindi samples.  
   - **Testing:** Tests pre-recorded samples in `Hindi recording/`.  
   - **Live Testing:** Records speech and predicts English translation in real-time.  

---

## How It Works  

1. **Recording & Playback:** Uses Windows API (`waveInOpen`, `waveOutWrite`) to capture and play audio.  
2. **Preprocessing:**  
   - DC shift removal  
   - Normalization  
   - Frame segmentation (sliding window)  
   - Hamming window application  
3. **Feature Extraction:**  
   - Autocorrelation to compute LPC coefficients  
   - Linear Predictive Coding (LPC)  
   - Cepstral coefficients  
   - Raised sine window to emphasize higher coefficients  
4. **Codebook Generation:**  
   - Uses LBG algorithm for vector quantization  
   - Saves codebooks for later use in HMM training  
5. **HMM Training & Prediction:**  
   - Trains HMMs for each word using Forward-Backward and Viterbi algorithms  
   - Computes probability of observed sequences for prediction  
6. **Prediction:**  
   - Takes live or pre-recorded speech  
   - Extracts features  
   - Computes probabilities using trained HMMs  
   - Outputs the corresponding **English word**  

---

## Future Enhancements  

- Add **Text-to-Speech (TTS)** to read English words aloud.  
- Extend to **continuous speech translation** for phrases and sentences.  
- Support more **Hindi words and phrases**.  
- Integrate with **modern speech recognition APIs** (Google Speech, OpenAI Whisper) for higher accuracy.  
- Build a **GUI interface** for easier use.  

---

**Input (spoken in Hindi):**  

