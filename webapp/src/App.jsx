import React from "react";
import { useState } from "react";

export function App() {

    const [username, setUsername] = useState('');
    const [password, setPassword] = useState('');

    const [labelInfo, setLabelInfo] = useState('');

    const onLoginClick = async () => {
        const response = await fetch('http://localhost:3000');
        const result = await response.json();
        setLabelInfo(response.title);
        console.log(result);
    };



    return (
        <div className="App">
            <label for = "username">Username</label>
            <input type="text" name="username" value= {username} onChange={(e) => setUsername(e.target.value)}></input>
            <label for = "password">Password</label>
            <input type="password" name="password" value= {password} onChange={(e) => setPassword(e.target.value)}></input>
            <button type="submit" onClick={() => onLoginClick()}>Login</button>
            <div>
                <label>Info </label>
                {username + ' ' + password}
            </div>
            <div>
                {labelInfo}
            </div>
        </div>
        
    );
};