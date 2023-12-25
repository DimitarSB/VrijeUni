package snake.logic

// you can alter this file!

sealed abstract class CellType {
  val isEmpty: Boolean
}

case class SnakeHead(direction: Direction) extends CellType {
  override val isEmpty: Boolean = false
}

/** 0 is just before SnakeHead, 1.0 is tail */
case class SnakeBody(distanceToHead: Float = 0f) extends CellType {
  override val isEmpty: Boolean = false
}

case class Empty() extends CellType {
  override val isEmpty: Boolean = true
}

case class Apple() extends CellType {
  override val isEmpty: Boolean = false
}

object CellType {
  def nonEmptyCellTypes : Set[CellType] = Set(SnakeHead(direction = East()), SnakeBody(), Apple())
}

