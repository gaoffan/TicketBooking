<template>
  <el-tabs :tab-position="tabpos" style="">
    <el-tab-pane label="记录修改">
    <search-card @search="search"></search-card>
    </el-tab-pane>
    <el-tab-pane label="新增记录">
    <el-card class="box-card">
    <el-form ref="form" :model="form" label-width="120px">
    <el-form-item label="车次" required>
        <el-input v-model="form.number"></el-input>
    </el-form-item>
    <el-form-item v-for="(station, index) in form.stations" :label="'途径 ' + index" :key="station.key" required>
        <el-input v-model="station.name"></el-input>
        <el-input class="time" placeholder="价格" v-model="station.price"></el-input>
        <el-time-select class="time" placeholder="出发时间" v-model="station.time" :picker-options="{start: '05:30',step: '00:01',end: '23:59'}"></el-time-select>
        <el-button size="small" type="danger" @click.prevent="removeStation(station)">删除</el-button>
    </el-form-item>
    <div class="btn2">
    <el-button class="btn2" type="success" @click="addStation">新增站点</el-button>
    </div>
    <el-form-item label="商务座数量" required>
        <el-input v-model="form.businessClass"></el-input>
    </el-form-item>
    <el-form-item label="一等座数量" required>
        <el-input v-model="form.firstClass"></el-input>
    </el-form-item>
    <el-form-item label="二等座数量" required>
        <el-input v-model="form.secondClass"></el-input>
    </el-form-item>
    <div class="bottom clearfix">
    <el-button class="btn" type="primary" @click="submitForm('form')">提交</el-button>
    <el-button class="btn" @click="resetForm('form')">重置</el-button>
    </div>
    </el-form>
  </el-card>
</el-tab-pane> 
</el-tabs>
</template>

<script>
  import SearchCard from './Controls/SearchCard.vue'
  export default {
    name: 'admin-page',
    components: {
      SearchCard
    },
    methods: {
      submitForm (formName) {
        this.$refs[formName].validate((valid) => {
          if (valid) {
            alert('submit!')
          } else {
            console.log('error submit!!')
            return false
          }
        })
      },
      resetForm (formName) {
        this.$refs[formName].resetFields()
      },
      removeStation (item) {
        var index = this.form.stations.indexOf(item)
        if (index !== -1) {
          this.form.stations.splice(index, 1)
        }
      },
      addStation () {
        this.form.stations.push({
          name: '',
          price: '',
          time: '',
          key: Date.now()
        })
      },
      search () {
        alert('aa')
      }
    },
    data () {
      return {
        tabpos: 'left',
        form: {
          number: '',
          businessClass: '',
          firstClass: '',
          secondClass: '',
          stations: [{ name: '', time: '', price: '' }]
        }
      }
    }
  }
</script>

<style>
  .btn {
    float: right;
    margin: 0.5rem;
  }
  .btn2 {
    text-align: center;
    margin: 0.5rem
  }
  .time {
      margin-top: 0.3rem;
  }
</style>
