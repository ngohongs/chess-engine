cmake_minimum_required(VERSION 3.16)
project(ngohongs)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fno-omit-frame-pointer")

add_executable(ngohongs src/main.cpp
                        src/CApplication.cpp src/CApplication.h
                        src/CGame.cpp src/CGame.h
                        src/CInterface.cpp src/CInterface.cpp
                        src/CCommand.h
                        src/CCommands/CCommandHelp.cpp src/CCommands/CCommandHelp.h
                        src/CCommands/CCommandQuit.cpp src/CCommands/CCommandQuit.h
                        src/CBoard.cpp src/CBoard.h
                        src/CPiece.cpp src/CPiece.h
                        src/EColor.h src/EPiece.h
        src/CPieces/CRook.cpp src/CPieces/CRook.h
        src/CPieces/CKnight.cpp src/CPieces/CKnight.h src/CPieces/CBishop.cpp src/CPieces/CBishop.h src/CPieces/CQueen.cpp src/CPieces/CQueen.h src/CPieces/CKing.cpp src/CPieces/CKing.h src/CPieces/CPawn.cpp src/CPieces/CPawn.h src/CCommands/CCommandBoard.cpp src/CCommands/CCommandBoard.h src/ETile.h src/CPieces/CEmpty.cpp src/CPieces/CEmpty.h src/EConst.h src/ETile.cpp src/FENTest.h src/CMove.cpp src/CMove.h src/CPieces/COffboard.cpp src/CPieces/COffboard.h src/EPiece.cpp src/EColor.cpp src/CHashKey.cpp src/CHashKey.h src/CHistory.cpp src/CHistory.h src/CPlayers/CPlayerHuman.cpp src/CPlayers/CPlayerHuman.h src/CCommands/CCommandMove.cpp src/CCommands/CCommandMove.h src/CPlayer.cpp src/CPlayer.h src/CPlayers/CPlayerAI.cpp src/CPlayers/CPlayerAI.h src/CCommands/CCommandPlay.cpp src/CCommands/CCommandPlay.h src/CCommands/CCommandSave.cpp src/CCommands/CCommandSave.h src/CCommands/CCommandLoad.cpp src/CCommands/CCommandLoad.h src/CCommands/CCommandRestart.cpp src/CCommands/CCommandRestart.h)