#include "control_panel.h"

ControlPanel::ControlPanel(QWidget *parent) : QWidget(parent) {
    direction = STAY;
    maxFloor = FLOOR_NUM;
    minFloor = 1;
    curFloor = 1;
    status = NO_TARGET;
    target = - 1;

    for (int i = minFloor; i <= maxFloor; ++i) {
        targets[i - 1] = false;
    }
}

void ControlPanel::addTarget(int floor) {
    status = HAS_TARGET;
    targets[floor - 1] = true;

    if (target == -1) {
        target = floor;
    }

    if ((direction == UP && floor > target) || (direction == DOWN && floor < target)) {
      target = floor;
    }

    next_target(floor);

    emit newTarget(floor);
}

void ControlPanel::removeTarget(int i) {
    if (status != HAS_TARGET) {
        return;
    }

    curFloor = i;
    targets[i - 1] = false;

    if (curFloor == target) {
        target = -1;
        getNewTarget();
    }

    if (next_target(i)) {
        emit newTarget(i);
    }
    else {
        status = NO_TARGET;
    }
}

void ControlPanel::getNewTarget() {
    bool state = false;

    if (direction == UP) {
        for (int i = FLOOR_NUM; i >= 1 && !state; i--) {
            if (targets[i - 1])  {
                state = true;
                target = i;
            }
        }
    } else {
        for (int i = 1; i <= FLOOR_NUM && !state; i++) {
            if (targets[i - 1]) {
                state = true;
                target = i;
            }
        }
    }
}



bool ControlPanel::next_target(int &floor) {
  bool state = false;
  if (target > curFloor) {
    bool flag = true;
    for (int i = curFloor; i <= FLOOR_NUM && flag; i += 1) {
      if (targets[i - 1]) {
        floor = i;
        state = true;
        flag = false;
      }
    }
  } else {
    bool flag = true;
    for (int i = curFloor; i >= 1 && flag; i -= 1) {
      if (targets[i - 1]) {
        floor = i;
        state = true;
        flag = false;
      }
    }
  }
  return state;
}


void ControlPanel::setDirection(int dir) {
    direction = dir;
}


int ControlPanel::getCurTarg() {
    return curFloor;
}

void ControlPanel::setCurTarg(int floor) {
    curFloor = floor;
}
