TARGET = ngohongs



BUILD_DIR = build
SOURCE_DIR = src
DOC_DIR = doc

CXX = g++
CXX_FLAGS = -Wall -pedantic -Wextra -std=c++14

.PHONY: all
all: compile

.PHONY: compile
compile: $(TARGET)

.PHONY: run
run:
	$(TARGET)
	./$(TARGET)

.PHONY: clean
clean:
	rm -rf $(TARGET) $(DOC_DIR) $(BUILD_DIR)/ 2>/dev/null

doc: // TODO header files
	doxygen Doxyfile


$(BUILD_DIR)/%.o:               src/%.cpp
							    mkdir -p $(BUILD_DIR)
							    $(CXX) $(CXX_FLAGS) $< -c -o $@

$(BUILD_DIR)/%.o:               src/*/%.cpp
								mkdir -p $(BUILD_DIR)
								$(CXX) $(CXX_FLAGS) $< -c -o $@

$(TARGET):                      $(BUILD_DIR)/main.o $(BUILD_DIR)/ETile.o $(BUILD_DIR)/EPiece.o $(BUILD_DIR)/EColor.o \
							    $(BUILD_DIR)/CPlayer.o $(BUILD_DIR)/CPiece.o $(BUILD_DIR)/CMove.o \
							    $(BUILD_DIR)/CInterface.o $(BUILD_DIR)/CHistory.o $(BUILD_DIR)/CHashKey.o \
							    $(BUILD_DIR)/CGame.o $(BUILD_DIR)/CBoard.o $(BUILD_DIR)/CApplication.o \
							    $(BUILD_DIR)/CCommandBoard.o $(BUILD_DIR)/CCommandHelp.o $(BUILD_DIR)/CCommandLoad.o \
							    $(BUILD_DIR)/CCommandMove.o $(BUILD_DIR)/CCommandPlay.o $(BUILD_DIR)/CCommandQuit.o \
							    $(BUILD_DIR)/CCommandRestart.o $(BUILD_DIR)/CCommandSave.o $(BUILD_DIR)/CBishop.o \
							    $(BUILD_DIR)/CEmpty.o $(BUILD_DIR)/CKing.o $(BUILD_DIR)/CKnight.o $(BUILD_DIR)/COffboard.o \
							    $(BUILD_DIR)/CPawn.o $(BUILD_DIR)/CQueen.o $(BUILD_DIR)/CRook.o $(BUILD_DIR)/CPlayerAI.o \
							    $(BUILD_DIR)/CPlayerHuman.o
							    mkdir -p $(BUILD_DIR)
							    $(CXX) $(CXX_FLAGS) $^ -o $@

$(BUILD_DIR)/CApplication.o:    src/CApplication.cpp src/CApplication.h src/CInterface.h \
                                src/CMove.h src/EPiece.h src/EColor.h src/ETile.h src/EConst.h \
                                src/CGame.h src/CBoard.h src/CPiece.h src/CPieces/CKing.h \
                                src/CPieces/CQueen.h src/CPieces/CBishop.h src/CPieces/CKnight.h \
                                src/CPieces/CRook.h src/CPieces/CPawn.h src/CPieces/CEmpty.h \
                                src/CPieces/COffboard.h src/CHashKey.h src/CHistory.h src/FENTest.h \
                                src/CPlayer.h src/CPlayers/CPlayerHuman.h src/CPlayers/CPlayerAI.h \
                                src/CCommand.h src/CCommands/CCommandHelp.h src/CCommands/CCommandQuit.h \
                                src/CCommands/CCommandBoard.h src/CCommands/CCommandMove.h \
                                src/CCommands/CCommandPlay.h src/CCommands/CCommandSave.h \
                                src/CCommands/CCommandLoad.h src/CCommands/CCommandRestart.h
$(BUILD_DIR)/CBoard.o:          src/CBoard.cpp src/CBoard.h src/CPiece.h src/CMove.h \
                                src/EPiece.h src/EColor.h src/ETile.h src/EConst.h src/CPieces/CKing.h \
                                src/CPieces/CQueen.h src/CPieces/CBishop.h src/CPieces/CKnight.h \
                                src/CPieces/CRook.h src/CPieces/CPawn.h src/CPieces/CEmpty.h \
                                src/CPieces/COffboard.h src/CHashKey.h src/CHistory.h src/FENTest.h
$(BUILD_DIR)/CGame.o:           src/CGame.cpp src/CGame.h src/CInterface.h src/CMove.h \
                                src/EPiece.h src/EColor.h src/ETile.h src/EConst.h src/CBoard.h \
                                src/CPiece.h src/CPieces/CKing.h src/CPieces/CQueen.h \
                                src/CPieces/CBishop.h src/CPieces/CKnight.h src/CPieces/CRook.h \
                                src/CPieces/CPawn.h src/CPieces/CEmpty.h src/CPieces/COffboard.h \
                                src/CHashKey.h src/CHistory.h src/FENTest.h src/CPlayer.h \
                                src/CPlayers/CPlayerHuman.h src/CPlayers/CPlayerAI.h
$(BUILD_DIR)/CHashKey.o:        src/CHashKey.cpp src/CHashKey.h src/CPiece.h src/CMove.h \
                                src/EPiece.h src/EColor.h src/ETile.h src/EConst.h
$(BUILD_DIR)/CHistory.o:        src/CHistory.cpp src/CHistory.h src/CMove.h src/EPiece.h \
                                src/EColor.h src/ETile.h src/EConst.h
$(BUILD_DIR)/CInterface.o:      src/CInterface.cpp src/CInterface.h src/CMove.h \
                                src/EPiece.h src/EColor.h src/ETile.h src/EConst.h
$(BUILD_DIR)/CMove.o:           src/CMove.cpp src/CMove.h src/EPiece.h src/EColor.h src/ETile.h \
                                src/EConst.h
$(BUILD_DIR)/CPiece.o:          src/CPiece.cpp src/CPiece.h src/CMove.h src/EPiece.h \
                                src/EColor.h src/ETile.h src/EConst.h
$(BUILD_DIR)/CPlayer.o:         src/CPlayer.cpp src/CPlayer.h src/CInterface.h src/CMove.h \
                                src/EPiece.h src/EColor.h src/ETile.h src/EConst.h src/CBoard.h \
                                src/CPiece.h src/CPieces/CKing.h src/CPieces/CQueen.h \
                                src/CPieces/CBishop.h src/CPieces/CKnight.h src/CPieces/CRook.h \
                                src/CPieces/CPawn.h src/CPieces/CEmpty.h src/CPieces/COffboard.h \
                                src/CHashKey.h src/CHistory.h src/FENTest.h
$(BUILD_DIR)/CCommandBoard.o:   src/CCommands/CCommandBoard.cpp \
                                src/CCommands/CCommandBoard.h src/CCommands/../CCommand.h \
                                src/CCommands/../CInterface.h src/CCommands/../CMove.h \
                                src/CCommands/../EPiece.h src/CCommands/../EColor.h \
                                src/CCommands/../ETile.h src/CCommands/../EConst.h \
                                src/CCommands/../CGame.h src/CCommands/../CBoard.h \
                                src/CCommands/../CPiece.h src/CCommands/../CPieces/CKing.h \
                                src/CCommands/../CPieces/CQueen.h src/CCommands/../CPieces/CBishop.h \
                                src/CCommands/../CPieces/CKnight.h src/CCommands/../CPieces/CRook.h \
                                src/CCommands/../CPieces/CPawn.h src/CCommands/../CPieces/CEmpty.h \
                                src/CCommands/../CPieces/COffboard.h src/CCommands/../CHashKey.h \
                                src/CCommands/../CHistory.h src/CCommands/../FENTest.h \
                                src/CCommands/../CPlayer.h src/CCommands/../CPlayers/CPlayerHuman.h \
                                src/CCommands/../CPlayers/CPlayerAI.h
$(BUILD_DIR)/CCommandHelp.o:    src/CCommands/CCommandHelp.cpp \
                                src/CCommands/CCommandHelp.h src/CCommands/../CCommand.h \
                                src/CCommands/../CInterface.h src/CCommands/../CMove.h \
                                src/CCommands/../EPiece.h src/CCommands/../EColor.h \
                                src/CCommands/../ETile.h src/CCommands/../EConst.h
$(BUILD_DIR)/CCommandLoad.o:    src/CCommands/CCommandLoad.cpp \
                                src/CCommands/CCommandLoad.h src/CCommands/../CGame.h \
                                src/CCommands/../CInterface.h src/CCommands/../CMove.h \
                                src/CCommands/../EPiece.h src/CCommands/../EColor.h \
                                src/CCommands/../ETile.h src/CCommands/../EConst.h \
                                src/CCommands/../CBoard.h src/CCommands/../CPiece.h \
                                src/CCommands/../CPieces/CKing.h src/CCommands/../CPieces/CQueen.h \
                                src/CCommands/../CPieces/CBishop.h src/CCommands/../CPieces/CKnight.h \
                                src/CCommands/../CPieces/CRook.h src/CCommands/../CPieces/CPawn.h \
                                src/CCommands/../CPieces/CEmpty.h src/CCommands/../CPieces/COffboard.h \
                                src/CCommands/../CHashKey.h src/CCommands/../CHistory.h \
                                src/CCommands/../FENTest.h src/CCommands/../CPlayer.h \
                                src/CCommands/../CPlayers/CPlayerHuman.h \
                                src/CCommands/../CPlayers/CPlayerAI.h src/CCommands/../CCommand.h
$(BUILD_DIR)/CCommandMove.o:    src/CCommands/CCommandMove.cpp \
                                src/CCommands/CCommandMove.h src/CCommands/../CCommand.h \
                                src/CCommands/../CInterface.h src/CCommands/../CMove.h \
                                src/CCommands/../EPiece.h src/CCommands/../EColor.h \
                                src/CCommands/../ETile.h src/CCommands/../EConst.h \
                                src/CCommands/../CGame.h src/CCommands/../CBoard.h \
                                src/CCommands/../CPiece.h src/CCommands/../CPieces/CKing.h \
                                src/CCommands/../CPieces/CQueen.h src/CCommands/../CPieces/CBishop.h \
                                src/CCommands/../CPieces/CKnight.h src/CCommands/../CPieces/CRook.h \
                                src/CCommands/../CPieces/CPawn.h src/CCommands/../CPieces/CEmpty.h \
                                src/CCommands/../CPieces/COffboard.h src/CCommands/../CHashKey.h \
                                src/CCommands/../CHistory.h src/CCommands/../FENTest.h \
                                src/CCommands/../CPlayer.h src/CCommands/../CPlayers/CPlayerHuman.h \
                                src/CCommands/../CPlayers/CPlayerAI.h
$(BUILD_DIR)/CCommandPlay.o:    src/CCommands/CCommandPlay.cpp \
                                src/CCommands/CCommandPlay.h src/CCommands/../CCommand.h \
                                src/CCommands/../CInterface.h src/CCommands/../CMove.h \
                                src/CCommands/../EPiece.h src/CCommands/../EColor.h \
                                src/CCommands/../ETile.h src/CCommands/../EConst.h \
                                src/CCommands/../CGame.h src/CCommands/../CBoard.h \
                                src/CCommands/../CPiece.h src/CCommands/../CPieces/CKing.h \
                                src/CCommands/../CPieces/CQueen.h src/CCommands/../CPieces/CBishop.h \
                                src/CCommands/../CPieces/CKnight.h src/CCommands/../CPieces/CRook.h \
                                src/CCommands/../CPieces/CPawn.h src/CCommands/../CPieces/CEmpty.h \
                                src/CCommands/../CPieces/COffboard.h src/CCommands/../CHashKey.h \
                                src/CCommands/../CHistory.h src/CCommands/../FENTest.h \
                                src/CCommands/../CPlayer.h src/CCommands/../CPlayers/CPlayerHuman.h \
                                src/CCommands/../CPlayers/CPlayerAI.h
$(BUILD_DIR)/CCommandQuit.o:    src/CCommands/CCommandQuit.cpp \
                                src/CCommands/CCommandQuit.h src/CCommands/../CCommand.h \
                                src/CCommands/../CInterface.h src/CCommands/../CMove.h \
                                src/CCommands/../EPiece.h src/CCommands/../EColor.h \
                                src/CCommands/../ETile.h src/CCommands/../EConst.h
$(BUILD_DIR)/CCommandRestart.o: src/CCommands/CCommandRestart.cpp \
                                src/CCommands/CCommandRestart.h src/CCommands/../CCommand.h \
                                src/CCommands/../CInterface.h src/CCommands/../CMove.h \
                                src/CCommands/../EPiece.h src/CCommands/../EColor.h \
                                src/CCommands/../ETile.h src/CCommands/../EConst.h \
                                src/CCommands/../CGame.h src/CCommands/../CBoard.h \
                                src/CCommands/../CPiece.h src/CCommands/../CPieces/CKing.h \
                                src/CCommands/../CPieces/CQueen.h src/CCommands/../CPieces/CBishop.h \
                                src/CCommands/../CPieces/CKnight.h src/CCommands/../CPieces/CRook.h \
                                src/CCommands/../CPieces/CPawn.h src/CCommands/../CPieces/CEmpty.h \
                                src/CCommands/../CPieces/COffboard.h src/CCommands/../CHashKey.h \
                                src/CCommands/../CHistory.h src/CCommands/../FENTest.h \
                                src/CCommands/../CPlayer.h src/CCommands/../CPlayers/CPlayerHuman.h \
                                src/CCommands/../CPlayers/CPlayerAI.h
$(BUILD_DIR)/CCommandSave.o:    src/CCommands/CCommandSave.cpp \
                                src/CCommands/CCommandSave.h src/CCommands/../CCommand.h \
                                src/CCommands/../CInterface.h src/CCommands/../CMove.h \
                                src/CCommands/../EPiece.h src/CCommands/../EColor.h \
                                src/CCommands/../ETile.h src/CCommands/../EConst.h \
                                src/CCommands/../CGame.h src/CCommands/../CBoard.h \
                                src/CCommands/../CPiece.h src/CCommands/../CPieces/CKing.h \
                                src/CCommands/../CPieces/CQueen.h src/CCommands/../CPieces/CBishop.h \
                                src/CCommands/../CPieces/CKnight.h src/CCommands/../CPieces/CRook.h \
                                src/CCommands/../CPieces/CPawn.h src/CCommands/../CPieces/CEmpty.h \
                                src/CCommands/../CPieces/COffboard.h src/CCommands/../CHashKey.h \
                                src/CCommands/../CHistory.h src/CCommands/../FENTest.h \
                                src/CCommands/../CPlayer.h src/CCommands/../CPlayers/CPlayerHuman.h \
                                src/CCommands/../CPlayers/CPlayerAI.h
$(BUILD_DIR)/CBishop.o:         src/CPieces/CBishop.cpp src/CPieces/CBishop.h \
                                src/CPieces/../CPiece.h src/CPieces/../CMove.h src/CPieces/../EPiece.h \
                                src/CPieces/../EColor.h src/CPieces/../ETile.h src/CPieces/../EConst.h \
                                src/CPieces/../CBoard.h src/CPieces/../CPieces/CKing.h \
                                src/CPieces/../CPieces/CQueen.h src/CPieces/../CPieces/CKnight.h \
                                src/CPieces/../CPieces/CRook.h src/CPieces/../CPieces/CPawn.h \
                                src/CPieces/../CPieces/CEmpty.h src/CPieces/../CPieces/COffboard.h \
                                src/CPieces/../CHashKey.h src/CPieces/../CHistory.h \
                                src/CPieces/../FENTest.h
$(BUILD_DIR)/CEmpty.o:          src/CPieces/CEmpty.cpp src/CPieces/CEmpty.h \
                                src/CPieces/../CPiece.h src/CPieces/../CMove.h src/CPieces/../EPiece.h \
                                src/CPieces/../EColor.h src/CPieces/../ETile.h src/CPieces/../EConst.h
$(BUILD_DIR)/CKing.o:           src/CPieces/CKing.cpp src/CPieces/CKing.h \
                                src/CPieces/../CPiece.h src/CPieces/../CMove.h src/CPieces/../EPiece.h \
                                src/CPieces/../EColor.h src/CPieces/../ETile.h src/CPieces/../EConst.h \
                                src/CPieces/../CBoard.h src/CPieces/../CPieces/CQueen.h \
                                src/CPieces/../CPieces/CBishop.h src/CPieces/../CPieces/CKnight.h \
                                src/CPieces/../CPieces/CRook.h src/CPieces/../CPieces/CPawn.h \
                                src/CPieces/../CPieces/CEmpty.h src/CPieces/../CPieces/COffboard.h \
                                src/CPieces/../CHashKey.h src/CPieces/../CHistory.h \
                                src/CPieces/../FENTest.h
$(BUILD_DIR)/CKnight.o:         src/CPieces/CKnight.cpp src/CPieces/CKnight.h \
                                src/CPieces/../CPiece.h src/CPieces/../CMove.h src/CPieces/../EPiece.h \
                                src/CPieces/../EColor.h src/CPieces/../ETile.h src/CPieces/../EConst.h \
                                src/CPieces/../CBoard.h src/CPieces/../CPieces/CKing.h \
                                src/CPieces/../CPieces/CQueen.h src/CPieces/../CPieces/CBishop.h \
                                src/CPieces/../CPieces/CRook.h src/CPieces/../CPieces/CPawn.h \
                                src/CPieces/../CPieces/CEmpty.h src/CPieces/../CPieces/COffboard.h \
                                src/CPieces/../CHashKey.h src/CPieces/../CHistory.h \
                                src/CPieces/../FENTest.h
$(BUILD_DIR)/COffboard.o:       src/CPieces/COffboard.cpp src/CPieces/COffboard.h \
                                src/CPieces/../CPiece.h src/CPieces/../CMove.h src/CPieces/../EPiece.h \
                                src/CPieces/../EColor.h src/CPieces/../ETile.h src/CPieces/../EConst.h
$(BUILD_DIR)/CPawn.o:           src/CPieces/CPawn.cpp src/CPieces/CPawn.h \
                                src/CPieces/../CPiece.h src/CPieces/../CMove.h src/CPieces/../EPiece.h \
                                src/CPieces/../EColor.h src/CPieces/../ETile.h src/CPieces/../EConst.h \
                                src/CPieces/../CBoard.h src/CPieces/../CPieces/CKing.h \
                                src/CPieces/../CPieces/CQueen.h src/CPieces/../CPieces/CBishop.h \
                                src/CPieces/../CPieces/CKnight.h src/CPieces/../CPieces/CRook.h \
                                src/CPieces/../CPieces/CEmpty.h src/CPieces/../CPieces/COffboard.h \
                                src/CPieces/../CHashKey.h src/CPieces/../CHistory.h \
                                src/CPieces/../FENTest.h
$(BUILD_DIR)/CQueen.o:          src/CPieces/CQueen.cpp src/CPieces/CQueen.h \
                                src/CPieces/../CPiece.h src/CPieces/../CMove.h src/CPieces/../EPiece.h \
                                src/CPieces/../EColor.h src/CPieces/../ETile.h src/CPieces/../EConst.h \
                                src/CPieces/../CBoard.h src/CPieces/../CPieces/CKing.h \
                                src/CPieces/../CPieces/CBishop.h src/CPieces/../CPieces/CKnight.h \
                                src/CPieces/../CPieces/CRook.h src/CPieces/../CPieces/CPawn.h \
                                src/CPieces/../CPieces/CEmpty.h src/CPieces/../CPieces/COffboard.h \
                                src/CPieces/../CHashKey.h src/CPieces/../CHistory.h \
                                src/CPieces/../FENTest.h
$(BUILD_DIR)/CRook.o:           src/CPieces/CRook.cpp src/CPieces/CRook.h \
                                src/CPieces/../CPiece.h src/CPieces/../CMove.h src/CPieces/../EPiece.h \
                                src/CPieces/../EColor.h src/CPieces/../ETile.h src/CPieces/../EConst.h \
                                src/CPieces/../CBoard.h src/CPieces/../CPieces/CKing.h \
                                src/CPieces/../CPieces/CQueen.h src/CPieces/../CPieces/CBishop.h \
                                src/CPieces/../CPieces/CKnight.h src/CPieces/../CPieces/CPawn.h \
                                src/CPieces/../CPieces/CEmpty.h src/CPieces/../CPieces/COffboard.h \
                                src/CPieces/../CHashKey.h src/CPieces/../CHistory.h \
                                src/CPieces/../FENTest.h
$(BUILD_DIR)/CPlayerAI.o:       src/CPlayers/CPlayerAI.cpp src/CPlayers/CPlayerAI.h \
                                src/CPlayers/../CPlayer.h src/CPlayers/../CInterface.h \
                                src/CPlayers/../CMove.h src/CPlayers/../EPiece.h \
                                src/CPlayers/../EColor.h src/CPlayers/../ETile.h \
                                src/CPlayers/../EConst.h src/CPlayers/../CBoard.h \
                                src/CPlayers/../CPiece.h src/CPlayers/../CPieces/CKing.h \
                                src/CPlayers/../CPieces/CQueen.h src/CPlayers/../CPieces/CBishop.h \
                                src/CPlayers/../CPieces/CKnight.h src/CPlayers/../CPieces/CRook.h \
                                src/CPlayers/../CPieces/CPawn.h src/CPlayers/../CPieces/CEmpty.h \
                                src/CPlayers/../CPieces/COffboard.h src/CPlayers/../CHashKey.h \
                                src/CPlayers/../CHistory.h src/CPlayers/../FENTest.h
$(BUILD_DIR)/CPlayerHuman.o:    src/CPlayers/CPlayerHuman.cpp src/CPlayers/CPlayerHuman.h \
                                src/CPlayers/../CPlayer.h src/CPlayers/../CInterface.h \
                                src/CPlayers/../CMove.h src/CPlayers/../EPiece.h \
                                src/CPlayers/../EColor.h src/CPlayers/../ETile.h \
                                src/CPlayers/../EConst.h src/CPlayers/../CBoard.h \
                                src/CPlayers/../CPiece.h src/CPlayers/../CPieces/CKing.h \
                                src/CPlayers/../CPieces/CQueen.h src/CPlayers/../CPieces/CBishop.h \
                                src/CPlayers/../CPieces/CKnight.h src/CPlayers/../CPieces/CRook.h \
                                src/CPlayers/../CPieces/CPawn.h src/CPlayers/../CPieces/CEmpty.h \
                                src/CPlayers/../CPieces/COffboard.h src/CPlayers/../CHashKey.h \
                                src/CPlayers/../CHistory.h src/CPlayers/../FENTest.h
$(BUILD_DIR)/EColor.o:          src/EColor.cpp src/EColor.h
$(BUILD_DIR)/EPiece.o:          src/EPiece.cpp src/EPiece.h
$(BUILD_DIR)/ETile.o:           src/ETile.cpp src/ETile.h
$(BUILD_DIR)/main.o:            src/main.cpp src/CApplication.h src/CInterface.h src/CMove.h \
                                src/EPiece.h src/EColor.h src/ETile.h src/EConst.h src/CGame.h \
                                src/CBoard.h src/CPiece.h src/CPieces/CKing.h src/CPieces/CQueen.h \
                                src/CPieces/CBishop.h src/CPieces/CKnight.h src/CPieces/CRook.h \
                                src/CPieces/CPawn.h src/CPieces/CEmpty.h src/CPieces/COffboard.h \
                                src/CHashKey.h src/CHistory.h src/FENTest.h src/CPlayer.h \
                                src/CPlayers/CPlayerHuman.h src/CPlayers/CPlayerAI.h src/CCommand.h \
                                src/CCommands/CCommandHelp.h src/CCommands/CCommandQuit.h \
                                src/CCommands/CCommandBoard.h src/CCommands/CCommandMove.h \
                                src/CCommands/CCommandPlay.h src/CCommands/CCommandSave.h \
                                src/CCommands/CCommandLoad.h src/CCommands/CCommandRestart.h

