#include "Browser.h"

Browser::Browser() {
    windows.append(Window());
}

void Browser::newWindow() {

    Window new_window = Window();
    windows.prepend(new_window);
}

void Browser::closeWindow() {

    if(windows.getSize() == 0){
        // No need to do anything
    }

    else{
        windows.removeNodeAtIndex(0);
    }
}

void Browser::switchToWindow(int index) { 

    if(index <= windows.getSize()-1){
        windows.moveToIndex(index, 0);
    }

    else{
        // Index is out of range, so there is no such winodws
    }
}

Window &Browser::getWindow(int index) {
    return windows.getNodeAtIndex(index) -> data;
}

void Browser::moveTab(Window &from, Window &to) {
    
    Tab to_be_copied = from.getActiveTab(); 
    Tab new_copied_tab = Tab(to_be_copied.getUrl(), to_be_copied.getTitle(), to_be_copied.getContents());

    to.newTab(new_copied_tab);
    
    //int index = to.tabs.getSize();
    //to.changeActiveTabTo(index-1); 
    
    from.closeTab(); 
    
}

void Browser::mergeWindows(Window &window1, Window &window2) {
    
    window2.changeActiveTabTo(0);
    
    while(!window2.isEmpty()){
        moveTab(window2, window1);
    }
    
}

void Browser::mergeAllWindows() {

    int tmp_size = windows.getSize();
    
    //first = windows.getNodeAtIndex(0)->data;
    
    for(int i = 1; i < tmp_size; i++){
        
        //tmp_window = windows.getNodeAtIndex(i)->data;
        
        windows.getNodeAtIndex(i)->data.changeActiveTabTo(0);

        while(!(windows.getNodeAtIndex(i)->data.isEmpty())){
        
            moveTab(windows.getNodeAtIndex(i)->data, windows.getNodeAtIndex(0)->data);
        }
    }
}

void Browser::closeAllWindows() {

    while(!windows.isEmpty()){
        closeWindow();
    }
}

void Browser::closeEmptyWindows() {

    int tmp_size = windows.getSize();
    
     for(int i = tmp_size-1; -1 < i ; i--){
         
        if(windows.getNodeAtIndex(i)->data.isEmpty()){            
            windows.removeNodeAtIndex(i);
        }
    }
}

void Browser::print() {
    Node<Window> *head = windows.getFirstNode();
    if(head == NULL) {
        std::cout << "The browser is empty" << std::endl;
    } else {
        (head -> data).print();
        head = head -> next;
        while(head != windows.getFirstNode()) {
            (head -> data).print();
            head = head -> next;
        }
    }
}