#!/usr/bin/env python3
import json
import sys

def read_config(file_path):
    """读取并解析JSON配置文件"""
    try:
        with open(file_path, 'r') as file:
            config = json.load(file)
        return config
    except FileNotFoundError:
        print(f"Error: Config file '{file_path}' not found.")
        sys.exit(1)
    except json.JSONDecodeError as e:
        print(f"Error: Invalid JSON format in config file: {e}")
        sys.exit(1)

def print_config(config):
    """格式化打印配置信息"""
    print("Robot Configuration:")
    print("====================")
    
    # 打印基本信息
    print(f"Name: {config.get('robot_name', 'Unknown')}")
    print(f"Health: {config.get('health', 0)}")
    print(f"Ammo: {config.get('ammo', 0)}")
    
    # 打印模块信息
    modules = config.get('enabled_modules', [])
    print(f"Enabled Modules: {', '.join(modules) if modules else 'None'}")
    
    # 打印所有配置项（可选）
    print("\nFull Configuration:")
    print("------------------")
    print(json.dumps(config, indent=2))

def main():
    """主函数"""
    # 检查命令行参数
    if len(sys.argv) != 2:
        print("Usage: python3 config_reader.py <config_file_path>")
        sys.exit(1)
    
    config_file = sys.argv[1]
    
    # 读取和打印配置
    config = read_config(config_file)
    print_config(config)

if __name__ == "__main__":
    main()
