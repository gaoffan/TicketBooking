<template>
  <el-tabs :tab-position="tabpos" style="">
    <el-tab-pane label="记录修改">
    <search-card @search="search"></search-card>
    </el-tab-pane>
    <el-tab-pane label="新增记录">
    <el-card class="box-card">
    <el-form ref="form" :model="form" label-width="120px" :inline="true">
    <el-form-item label="出发地" required>
      <el-input v-model="form.departure"></el-input>
    </el-form-item>
    <el-form-item label="到达地" required>
        <el-input v-model="form.arrival"></el-input>
    </el-form-item>
    <el-form-item label="日期" required>
        <el-date-picker v-model="form.departureDate" align="right" type="date" placeholder="请选择日期" :picker-options="pickerOptions1"></el-date-picker>
    </el-form-item>
    <el-form-item label="时间" required>
        <el-time-select placeholder="出发时间" v-model="form.startTime" :picker-options="{start: '05:30',step: '00:01',end: '23:59'}"></el-time-select>
        <el-time-select placeholder="到达时间" v-model="form.endTime" :picker-options="{ start: '05:30',step: '00:01',end: '23:59',minTime: startTime}"></el-time-select>
    </el-form-item>
    <el-form-item label="商务座数量" required>
        <el-input v-model="form.businessClass"></el-input>
    </el-form-item>
    <el-form-item label="一等座数量" required>
        <el-input v-model="form.firstClass"></el-input>
    </el-form-item>
    <el-form-item label="二等座数量" required>
        <el-input v-model="form.secondClass"></el-input>
    </el-form-item>
     <el-form-item>
    <el-button type="primary" @click="submitForm('form')">提交</el-button>
    <el-button @click="resetForm('form')">重置</el-button>
    </el-form-item>
    </el-form>
  </el-card>
    </el-tab-pane>
    
  </el-tabs>

  
</template>

<script>
  import SearchCard from './Controls/SearchCard.vue'
  export default {
    name: 'main-page',
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
      removeDomain (item) {
        var index = this.form.stations.indexOf(item)
        if (index !== -1) {
          this.form.stations.splice(index, 1)
        }
      },
      addDomain () {
        this.form.stations.push({
          value: '',
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
          departure: '',
          arrival: '',
          departureDate: '',
          businessClass: '',
          firstClass: '',
          secondClass: '',
          startTime: '',
          endTime: ''
        }
      }
    }
  }
</script>

<style>
  
</style>
