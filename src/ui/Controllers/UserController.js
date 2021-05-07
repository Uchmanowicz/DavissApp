function userStatusToText(statusNo) {
    var text = ""
    switch(statusNo){
    case 0:
        text = "";
        break;
    case 1:
        text = "Login or password is incorrect";
        break;
    case 2:
        text = "User has beed blocked. Please contact with admin";
        break;
    case 3:
        text = "User already exists";
        break;
    case 4:
        text = "Error with connection to network. Please check your network";
        break;
    case 5:
        text = "Occured not known error";
        break;
    }
    return text;
}
