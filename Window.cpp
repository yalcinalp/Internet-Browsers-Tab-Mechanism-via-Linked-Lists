#include "Window.h"

Window::Window() {
  this->activeTab = 0;
  tabs.append(Tab());
}

Tab Window::getActiveTab() {
  if (tabs.isEmpty()) {
    Tab empty_tab = Tab();
    return empty_tab;
  }

  else {
    return tabs.getNodeAtIndex(activeTab)->data;
  }
}

bool Window::isEmpty() const { return tabs.isEmpty(); }

void Window::newTab(const Tab &tab) {
  if (tabs.getSize() == 0) {
    tabs.append(tab);
    activeTab = 0;
  }

  else {
    tabs.insertAfterNode(tab, tabs.getNodeAtIndex(activeTab));
    activeTab++;
  }
}

void Window::closeTab() {
  if (tabs.isEmpty()) {
    activeTab = -1;
  }

  else {
    if (activeTab == 0 && tabs.getSize() == 1) {
      tabs.removeNodeAtIndex(activeTab);
      activeTab = -1;

    }

    else if (activeTab == tabs.getSize() - 1) {
      // case for closing the last tab

      tabs.removeNodeAtIndex(activeTab);
      activeTab--;
    }

    else {
      // Normal case (somewhere in the middle)

      tabs.removeNodeAtIndex(activeTab);

      // we didnt need to change the active tab integer since logically it
      // happens automatically
    }
  }
}

void Window::moveActiveTabTo(int index) {
  if (!tabs.isEmpty()) {
    if (index > tabs.getSize() - 1) {
      tabs.moveToIndex(activeTab, tabs.getSize() - 1);
      activeTab = tabs.getSize() - 1;
    }

    else {
      tabs.moveToIndex(activeTab, index);
      activeTab = index;
    }
  }

  else {
  }
}

void Window::changeActiveTabTo(int index) {
  if (index > tabs.getSize() - 1) {
  }

  else {
    if (index < 0) {
      // do nothin
    }

    else {
      activeTab = index;
    }
  }
}

void Window::addTab(Node<Tab> &tab) {
  if (tabs.isEmpty()) {
    tabs.append(tab.data);
    activeTab = 0;
  }

  else {
    tabs.append(tab.data);
  }
}

void Window::print() {
  if (tabs.isEmpty())
    std::cout << "Window is empty" << std::endl;
  else
    std::cout << "The active tab is tab " << activeTab << std::endl;
  tabs.print();
}
