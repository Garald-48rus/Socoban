#include "level.h"

Level::Level()
{

}
//------------------------------------------------------------------------------
void Level::reset()
{
    load(mLevel);
}
//------------------------------------------------------------------------------
void Level::load(int aLevel)
{

 const auto &lp =  appSetings::instanse().levelsPath();//получаю имя файла хранящий уровни

 QString lvl_path = lp + QString::number(aLevel) + ".lvl";//формирую полный адрес уровня

  QFile   file(lvl_path);

  mIsLoad       = false;
  mIsComplete   = false;
  mGoalCount    = 0;
  mBoxesOnGoal  = 0;
  mSteps        = 0;

  file.open(QIODevice::ReadOnly);

  if(file.isOpen())
  {
    mRoom.clear();

    QTextStream in(&file);
    in >> mLevel;
    in >> mColumns;
    in >> mLines;

    std::vector<eField> tmpRoom(mColumns * mLines, eField::EMPTY);//заполняю временный вектор  пустыми полями

    in.readLine();

    for(int i = 0; i < mLines; ++i)
    {
      QString line;
      line = in.readLine();

      int  column = 0;
      int  end    = line.size();

      while(column != end)
      {
        switch (line[column].toLatin1())
        {
          case '#': // Wall
          {
            tmpRoom[mColumns * i + column] =  eField::WALL;
            break;
          }
          case '@': // Player
          {
            tmpRoom[mColumns * i + column] =  eField::PLAYER;
            mPlayerPos.first  = i;
            mPlayerPos.second = column;
            break;
          }
          case '+': // Player on goal square
          {
            tmpRoom[mColumns * i + column] =  eField::PLAYER_ON_GOAL;
            break;
          }
          case '$': // Box
          {
            tmpRoom[mColumns * i + column] =  eField::BOX;
            break;
          }
          case '*': // Box on goal square
          {
            tmpRoom[mColumns * i + column] =  eField::BOX_ON_GOAL;
            ++mGoalCount;
            ++mBoxesOnGoal;
            break;
          }
          case '.': // Goal square
          {
            tmpRoom[mColumns * i + column] =  eField::GOAL;
            ++mGoalCount;
            break;
          }
          case ' ': // Floor or Empty
          {
            tmpRoom[mColumns * i + column] = eField::EMPTY;
            break;
          }
      }
      ++column;
    }
  }
    mRoom.swap(tmpRoom); //меняю данные из временного вектора в нашу комнату
    mIsLoad = true;//ставлю флаг загрузки уровня в true
  }

  file.close();

}
//------------------------------------------------------------------------------
void Level::load(std::string)
{
}
//------------------------------------------------------------------------------
bool Level::isComplete()
{
  return mIsComplete;
}
//------------------------------------------------------------------------------
bool Level::isLoad()
{
  return mIsLoad;
}
//------------------------------------------------------------------------------
void Level::player_up()
{
    _move(-1,0);
}
//------------------------------------------------------------------------------
void Level::player_down()
{
    _move(1,0);
}
//------------------------------------------------------------------------------
void Level::player_left()
{
    _move(0 , -1);
}
//------------------------------------------------------------------------------
void Level::player_rigth()
{
    _move(0, 1);
}
//-----------------------------------------------------
void Level::_move(int aDl, int aDc) //функция смещения по осям
{
    auto &[line, column] = mPlayerPos; //передаю позицию игрока

        auto nl  = line   + aDl;                // next line
        auto nc  = column + aDc;                // next column

        auto nnl = nl + aDl;                    // next next line
        auto nnc = nc + aDc;                    // next next column

        auto coff  = mColumns * line + column;  // current offset
        auto noff  = mColumns * nl + nc;        // next offset
        auto nnoff = mColumns * nnl + nnc;      // next next offset

        auto &f   = mRoom[coff];                 // current field
        auto &nf  = mRoom[noff];                 // next field
        auto &nnf = mRoom[nnoff];                // next next field


       bool isMoving = false; //флаг можно ли двигаться или нет

              switch(nf)
              {
                case eField::BOX:
                {
                  if(nnf == eField::GOAL)
                  {
                    f   = (f == eField::PLAYER) ? eField::EMPTY : eField::GOAL;
                    nf  = eField::PLAYER;
                    nnf = eField::BOX_ON_GOAL;
                    isMoving = true;
                    ++mBoxesOnGoal;
                    break;
                  }
                  if(nnf == eField::EMPTY)
                  {
                    f   = (f == eField::PLAYER) ? eField::EMPTY : eField::GOAL;
                    nf  = eField::PLAYER;
                    nnf = eField::BOX;
                    isMoving = true;
                    break;
                  }
                  break;
                }
                case eField::BOX_ON_GOAL:
                {
                  if(nnf == eField::GOAL)
                  {
                    f   = (f == eField::PLAYER) ? eField::EMPTY : eField::GOAL;
                    nf  = eField::PLAYER_ON_GOAL;
                    nnf = eField::BOX_ON_GOAL;
                    isMoving = true;
                    break;
                  }
                  if(nnf == eField::EMPTY)
                  {
                    f   = (f == eField::PLAYER) ? eField::EMPTY : eField::GOAL;
                    nf  = eField::PLAYER_ON_GOAL;
                    nnf = eField::BOX;
                    isMoving = true;
                    --mBoxesOnGoal;
                    break;
                  }
                  break;
                }
                case eField::GOAL:
                {
                  f   = (f == eField::PLAYER) ? eField::EMPTY : eField::GOAL;
                  nf  = eField::PLAYER_ON_GOAL;
                  isMoving = true;
                  break;
                }
                case eField::EMPTY:
                {
                  f  = (f == eField::PLAYER) ? eField::EMPTY : eField::GOAL;
                  nf = eField::PLAYER;
                  isMoving = true;
                  break;
                }
                case eField::WALL:
                case eField::PLAYER:
                case eField::PLAYER_ON_GOAL:
                  break;
              }

              if(isMoving)//если ирок двинулся
              {
                //меняю координаты игрока
                line   = nl;
                column = nc;
                //увиличиваю кол шагов
                ++mSteps;

                if( mBoxesOnGoal == mGoalCount) //если все ящики на месте
                  mIsComplete = true; //флаг завершения уровня ставлю в true
              }
}
//------------------------------------------------------------------------------
int Level::steps_count() const
{
  return mSteps;
}
//------------------------------------------------------------------------------
int Level::goals() const
{
  return mGoalCount;
}
//------------------------------------------------------------------------------
int Level::boxes_on_goal() const
{
  return mBoxesOnGoal;
}
